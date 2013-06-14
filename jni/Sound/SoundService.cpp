#include "SoundService.hpp"
#include "Resource.hpp"
#include "Log.hpp"

namespace Core
{
    SoundService::SoundService() :
        mEngineObj(NULL), mEngine(NULL),
        mOutputMixObj(NULL),
        mBGMPlayerObj(NULL), mBGMPlayer(NULL), mBGMPlayerSeek(NULL),
        mPlayerObj(NULL), mPlayer(NULL), mPlayerQueue(NULL),
        mSounds(), mSoundCount(0)
    {
        LOGI("Creating SoundService.");
    }


    SoundService::~SoundService()
    {
        LOGI("Destroying SoundService.");

        for (int32_t i = 0; i < mSoundCount; ++i)
        {
            delete mSounds[i];
            mSoundCount = 0;
        }
    }

    Status SoundService::Start()
    {
        LOGI("Starting SoundService.");
        SLresult lRes;
        const SLuint32      lEngineMixIIDCount = 1;
        const SLInterfaceID lEngineMixIIDs[]   = {SL_IID_ENGINE};
        const SLboolean     lEngineMixReqs[]   = {SL_BOOLEAN_TRUE};
        const SLuint32      lOutputMixIIDCount = 0;
        const SLInterfaceID lOutputMixIIDs[]   = {};
        const SLboolean     lOutputMixReqs[]   = {};

        // Creates OpenSL ES engine and dumps its capabilities.
        lRes = slCreateEngine(&mEngineObj, 0, NULL,
            lEngineMixIIDCount, lEngineMixIIDs, lEngineMixReqs);
        if (lRes != SL_RESULT_SUCCESS)
        {
        	goto ERROR;
        }
        lRes = (*mEngineObj)->Realize(mEngineObj,SL_BOOLEAN_FALSE);
        if (lRes != SL_RESULT_SUCCESS)
        {
        	goto ERROR;
        }
        lRes = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine);
        if (lRes != SL_RESULT_SUCCESS)
        {
        	goto ERROR;
        }

        // Creates audio output.
        lRes = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);
        lRes = (*mOutputMixObj)->Realize(mOutputMixObj, SL_BOOLEAN_FALSE);

        // Set-up sound player.
        if (StartSoundPlayer() != STATUS_OK)
        {
        	goto ERROR;
        }

        // Loads resources
        for (int32_t i = 0; i < mSoundCount; ++i)
        {
            if (mSounds[i]->Load() != STATUS_OK)
            {
            	goto ERROR;
            }
        }
        return STATUS_OK;

    ERROR:
        LOGE("Error while starting SoundService");
        Stop();
        return STATUS_KO;
    }

    void SoundService::Stop()
    {
    	LOGI("Stopping SoundService.");

        // Stops and destroys BGM player.
        StopBGM();

        // Destroys sound player.
        if (mPlayerObj != NULL)
        {
            (*mPlayerObj)->Destroy(mPlayerObj);
            mPlayerObj = NULL; mPlayer = NULL; mPlayerQueue = NULL;
        }

        // Destroys audio output and engine.
        if (mOutputMixObj != NULL)
        {
            (*mOutputMixObj)->Destroy(mOutputMixObj);
            mOutputMixObj = NULL;
        }
        if (mEngineObj != NULL)
        {
            (*mEngineObj)->Destroy(mEngineObj);
            mEngineObj = NULL; mEngine = NULL;
        }

        // Frees sound resources.
        for (int32_t i = 0; i < mSoundCount; ++i)
        {
            mSounds[i]->Unload();
        }
    }

    Status SoundService::StartSoundPlayer()
    {
    	LOGI("Starting sound player.");
        SLresult lRes;

        // Set-up sound audio source.
        SLDataLocator_AndroidSimpleBufferQueue lDataLocatorIn;
        lDataLocatorIn.locatorType =
            SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
        // At most one buffer in the queue.
        lDataLocatorIn.numBuffers = 1;

        SLDataFormat_PCM lDataFormat;
        lDataFormat.formatType = SL_DATAFORMAT_PCM;
        lDataFormat.numChannels = 1; // Mono sound.
        lDataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
        lDataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
        lDataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
        lDataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
        lDataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;

        SLDataSource lDataSource;
        lDataSource.pLocator = &lDataLocatorIn;
        lDataSource.pFormat = &lDataFormat;

        SLDataLocator_OutputMix lDataLocatorOut;
        lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
        lDataLocatorOut.outputMix = mOutputMixObj;

        SLDataSink lDataSink;
        lDataSink.pLocator = &lDataLocatorOut;
        lDataSink.pFormat = NULL;

        // Creates the sounds player and retrieves its interfaces.
        const SLuint32 lSoundPlayerIIDCount = 2;
        const SLInterfaceID lSoundPlayerIIDs[] =
            { SL_IID_PLAY, SL_IID_BUFFERQUEUE };
        const SLboolean lSoundPlayerReqs[] =
            { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

        lRes = (*mEngine)->CreateAudioPlayer(mEngine, &mPlayerObj,
            &lDataSource, &lDataSink, lSoundPlayerIIDCount,
            lSoundPlayerIIDs, lSoundPlayerReqs);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        lRes = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY,
            &mPlayer);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mPlayerObj)->GetInterface(mPlayerObj,
            SL_IID_BUFFERQUEUE, &mPlayerQueue);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        // Starts the sound player. Nothing can be heard while the
        // sound queue remains empty.
        lRes = (*mPlayer)->SetPlayState(mPlayer,
            SL_PLAYSTATE_PLAYING);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        return STATUS_OK;

    ERROR:
        LOGE("Error while starting SoundPlayer");
        return STATUS_KO;
    }

    Status SoundService::PlayBGM(const char* pPath)
    {
        SLresult lRes;
        LOGI("Opening BGM %s", pPath);

        // Set-up BGM audio source.
        Asset lResource(pPath);
        AssetDescriptor lDescriptor = lResource.Descript();
        if (lDescriptor.mDescriptor < 0)
        {
            LOGE("Could not open BGM file");
            return STATUS_KO;
        }

        SLDataLocator_AndroidFD lDataLocatorIn;
        lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
        lDataLocatorIn.fd          = lDescriptor.mDescriptor;
        lDataLocatorIn.offset      = lDescriptor.mStart;
        lDataLocatorIn.length      = lDescriptor.mLength;

        SLDataFormat_MIME lDataFormat;
        lDataFormat.formatType    = SL_DATAFORMAT_MIME;
        lDataFormat.mimeType      = NULL;
        lDataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;
       // Here you can set USB settings.
        SLDataSource lDataSource;
        lDataSource.pLocator = &lDataLocatorIn;
        lDataSource.pFormat  = &lDataFormat;

        SLDataLocator_OutputMix lDataLocatorOut;
        lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
        lDataLocatorOut.outputMix   = mOutputMixObj;

        SLDataSink lDataSink;
        lDataSink.pLocator = &lDataLocatorOut;
        lDataSink.pFormat  = NULL;

        // Creates BGM player and retrieves its interfaces.
        const SLuint32 lBGMPlayerIIDCount = 2;
        const SLInterfaceID lBGMPlayerIIDs[] =
            { SL_IID_PLAY, SL_IID_SEEK };
        const SLboolean lBGMPlayerReqs[] =
            { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

        lRes = (*mEngine)->CreateAudioPlayer(mEngine,
            &mBGMPlayerObj, &lDataSource, &lDataSink,
            lBGMPlayerIIDCount, lBGMPlayerIIDs, lBGMPlayerReqs);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mBGMPlayerObj)->Realize(mBGMPlayerObj,
            SL_BOOLEAN_FALSE);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        lRes = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj,
            SL_IID_PLAY, &mBGMPlayer);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj,
            SL_IID_SEEK, &mBGMPlayerSeek);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        // Enables looping and starts playing.
        lRes = (*mBGMPlayerSeek)->SetLoop(mBGMPlayerSeek,
            SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        lRes = (*mBGMPlayer)->SetPlayState(mBGMPlayer,
            SL_PLAYSTATE_PLAYING);
        if (lRes != SL_RESULT_SUCCESS) goto ERROR;

        return STATUS_OK;

    ERROR:
        return STATUS_KO;
    }

    void SoundService::StopBGM()
    {
        if (mBGMPlayer != NULL)
        {
            SLuint32 lBGMPlayerState;
            (*mBGMPlayerObj)->GetState(mBGMPlayerObj,&lBGMPlayerState);
            if (lBGMPlayerState == SL_OBJECT_STATE_REALIZED)
            {
                (*mBGMPlayer)->SetPlayState(mBGMPlayer,SL_PLAYSTATE_PAUSED);
                (*mBGMPlayerObj)->Destroy(mBGMPlayerObj);
                mBGMPlayerObj = NULL;
                mBGMPlayer = NULL; mBGMPlayerSeek = NULL;
            }
        }
    }

    Sound* SoundService::RegisterSound(const char* pPath)
    {
        // Finds out if texture already loaded.
        for (int32_t i = 0; i < mSoundCount; ++i)
        {
            if (strcmp(pPath, mSounds[i]->GetPath()) == 0)
            {
                return mSounds[i];
            }
        }

        Sound* lSound = new Sound(pPath);
        mSounds[mSoundCount++] = lSound;
        return lSound;
    }

    void SoundService::PlaySound(Sound* pSound)
    {
        SLresult lRes;
        SLuint32 lPlayerState;
        (*mPlayerObj)->GetState(mPlayerObj, &lPlayerState);
        if (lPlayerState == SL_OBJECT_STATE_REALIZED)
        {
            int16_t* lBuffer = (int16_t*) pSound->mBuffer;
            off_t    lLength = pSound->mLength;

            // Removes any sound from the queue.
            lRes = (*mPlayerQueue)->Clear(mPlayerQueue);
            if (lRes != SL_RESULT_SUCCESS) goto ERROR;

            // Plays the new sound.
            lRes = (*mPlayerQueue)->Enqueue(mPlayerQueue, lBuffer,
                lLength);
            if (lRes != SL_RESULT_SUCCESS) goto ERROR;
        }
        return;

    ERROR:
        LOGE("Error trying to play sound");
    }
}