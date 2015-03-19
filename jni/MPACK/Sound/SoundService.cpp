#include "SoundService.hpp"

#include "Log.hpp"
#include "Global.hpp"
#include "OutputMixer.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		SoundService::SoundService()
		   : m_engineObj(NULL), m_engine(NULL),
			mBGMPlayerObj(NULL), mBGMPlayer(NULL)
		{
			LOGI("Creating SoundService.");
		}

		SoundService::~SoundService()
		{
			LOGI("Destroying SoundService.");
		}

		ReturnValue SoundService::Start()
		{
			LOGI("Starting SoundService.");

			SLresult res;
			const SLuint32      engineMixIIDCount = 0;
			const SLInterfaceID engineMixIIDs[]   = {};
			const SLboolean     engineMixReqs[]   = {};

			// Creates OpenSL ES engine and dumps its capabilities.
			res = slCreateEngine(&m_engineObj, 0, NULL, engineMixIIDCount, engineMixIIDs, engineMixReqs);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SoundService::Start() at slCreateEngine");
				goto ERROR;
			}
			res = (*m_engineObj)->Realize(m_engineObj,SL_BOOLEAN_FALSE);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SoundService::Start() at (*m_engineObj)->Realize");
				goto ERROR;
			}
			res = (*m_engineObj)->GetInterface(m_engineObj, SL_IID_ENGINE, &m_engine);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SoundService::Start() at (*m_engineObj)->GetInterface");
				goto ERROR;
			}

			if(!OutputMixer::GetOutputMixer())
			{
				goto FAIL;
			}

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("SoundService::Start() error: res = %d", res);
			goto ERROR_EXIT;

		FAIL:
			LOGE("SoundService::Start() failed");
			goto ERROR_EXIT;

		ERROR_EXIT:
			Stop();
			return RETURN_VALUE_KO;
		}

		void SoundService::Stop()
		{
			LOGI("Stopping SoundService.");
			// Stops and destroys BGM player.
			//StopBGM();
			if (mBGMPlayerObj != NULL)
			{
				(*mBGMPlayerObj)->Destroy(mBGMPlayerObj);
				mBGMPlayerObj = NULL; mBGMPlayer = NULL; mBGMPlayerQueue = NULL;
			}

			OutputMixer::DestroyOutputMixer();

			if (m_engineObj != NULL)
			{
				(*m_engineObj)->Destroy(m_engineObj);
				m_engineObj = NULL;
				m_engine = NULL;
			}
		}

		SLEngineItf& SoundService::GetOpenSLEngine()
		{
			return m_engine;
		}

		ReturnValue SoundService::Test()
		{
			SLresult lRes;

			/*
			SLDataLocator_AndroidSimpleBufferQueue lDataLocatorIn;
			lDataLocatorIn.locatorType =
				SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
			// At most one buffer in the queue.
			lDataLocatorIn.numBuffers = 1;
			*/

			/*Sound *snd;
			snd = mPlaylist->GetSound();

			SLDataLocator_Address lDataLocatorIn = {SL_DATALOCATOR_ADDRESS, snd->GetPCMData(), snd->GetPCMLength()};
			*/

			// use asset manager to open asset by filename
			AAsset* asset = AAssetManager_open(pAAssetManager, "Sounds/bgm.mp3", AASSET_MODE_UNKNOWN);

			// the asset might not be found
			if (NULL == asset) {
				return JNI_FALSE;
			}

			// open asset as file descriptor
			off_t start, length;
			int fd = AAsset_openFileDescriptor(asset, &start, &length);
			if(fd<0)
			{
				lRes=-1;
				//goto ERROR;
			}
			AAsset_close(asset);

			// configure audio source
			SLDataLocator_AndroidFD lDataLocatorIn = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
			SLDataFormat_MIME lDataFormat = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};

			SLDataSource lDataSource;
			lDataSource.pLocator = &lDataLocatorIn;
			lDataSource.pFormat  = &lDataFormat;


			// configure audio sink
			SLDataLocator_OutputMix lDataLocatorOut;
			lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
			lDataLocatorOut.outputMix   = OutputMixer::GetOutputMixer()->GetObjectItf();

			SLDataSink lDataSink;
			lDataSink.pLocator = &lDataLocatorOut;
			lDataSink.pFormat  = NULL;

			LOGD("BGM 1");

			// Creates BGM player and retrieves its interfaces.
			const SLuint32 lBGMPlayerIIDCount = 1;
			const SLInterfaceID lBGMPlayerIIDs[] =
				{ SL_IID_PLAY};
			const SLboolean lBGMPlayerReqs[] =
				{ SL_BOOLEAN_TRUE};

			lRes = (*m_engine)->CreateAudioPlayer(m_engine,
				&mBGMPlayerObj, &lDataSource, &lDataSink,
				lBGMPlayerIIDCount, lBGMPlayerIIDs, lBGMPlayerReqs);
			LOGD("BGM 1.0.1");
			if (lRes != SL_RESULT_SUCCESS) goto ERROR;

			LOGD("BGM 1.1");

			lRes = (*mBGMPlayerObj)->Realize(mBGMPlayerObj,
				SL_BOOLEAN_FALSE);
			if (lRes != SL_RESULT_SUCCESS) goto ERROR;


			LOGD("BGM 2");

			lRes = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj,
				SL_IID_PLAY, &mBGMPlayer);
			if (lRes != SL_RESULT_SUCCESS) goto ERROR;

			/*lRes = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj,
					SL_IID_BUFFERQUEUE, &mBGMPlayerQueue);
			if (lRes != SL_RESULT_SUCCESS) goto ERROR;
			*/

			LOGD("BGM 3");


			LOGD("PlayBGMPlaylist 1");

			LOGD("PlayBGMPlaylist 2");

			lRes = (*mBGMPlayer)->SetPlayState(mBGMPlayer,
				SL_PLAYSTATE_PLAYING);
			if (lRes != SL_RESULT_SUCCESS) goto ERROR;

			LOGD("PlayBGMPlaylist 3");

			LOGD("PlayBGMPlaylist 4");

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("Error while starting playlisy lRes = %d",lRes);

			return RETURN_VALUE_KO;
		}
	}
}
