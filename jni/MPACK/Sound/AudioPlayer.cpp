#include "AudioPlayer.hpp"

#include "SoundService.hpp"
#include "Global.hpp"
#include "Context.hpp"
#include "OutputMixer.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		AudioPlayer::AudioPlayer()
			: m_path(), m_audioPlayerObj(NULL), m_audioPlayer(NULL)
		{
		}

		AudioPlayer::~AudioPlayer()
		{
			Unload();
		}

		std::string AudioPlayer::GetPath() const
		{
			return m_path;
		}

		Core::ReturnValue AudioPlayer::Load(string path)
		{
			SLEngineItf &engine=Global::pContext->pSoundService->GetOpenSLEngine();

			AAsset* asset = AAssetManager_open(pAAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);

			off_t start, length;
			int fileDescriptor = AAsset_openFileDescriptor(asset, &start, &length);
			if(fileDescriptor<0)
			{
				LOGE("AudioPlayer::Load() error: failed to open file descriptor for: %s",path.c_str());
				return RETURN_VALUE_KO;
			}
			AAsset_close(asset);

			SLDataLocator_AndroidFD dataLocatorIn = {SL_DATALOCATOR_ANDROIDFD, fileDescriptor, start, length};
			SLDataFormat_MIME dataFormat = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};

			SLDataSource dataSource;
			dataSource.pLocator = &dataLocatorIn;
			dataSource.pFormat  = &dataFormat;

			SLDataLocator_OutputMix dataLocatorOut;
			dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
			dataLocatorOut.outputMix   = OutputMixer::GetOutputMixer()->GetObjectItf();

			SLDataSink dataSink;
			dataSink.pLocator = &dataLocatorOut;
			dataSink.pFormat  = NULL;

			const SLuint32 audioPlayerIIDCount = 1;
			const SLInterfaceID audioPlayerIIDs[] =	{ SL_IID_PLAY };
			const SLboolean audioPlayerReqs[] = { SL_BOOLEAN_TRUE };

			SLresult res = (*engine)->CreateAudioPlayer(engine, &m_audioPlayerObj, &dataSource, &dataSink, audioPlayerIIDCount, audioPlayerIIDs, audioPlayerReqs);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*engine)->CreateAudioPlayer");
				goto ERROR;
			}

			res = (*m_audioPlayerObj)->Realize(m_audioPlayerObj, SL_BOOLEAN_FALSE);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->Realize");
				goto ERROR;
			}

			res = (*m_audioPlayerObj)->GetInterface(m_audioPlayerObj, SL_IID_PLAY, &m_audioPlayer);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->GetInterface");
				goto ERROR;
			}

			m_path=path;
			return RETURN_VALUE_OK;

		ERROR:
			LOGE("AudioPlayer()::Load(\"%s\") error: res = %d ",path.c_str(),res);
			return RETURN_VALUE_KO;
		}

		void AudioPlayer::Unload()
		{
			if (m_audioPlayerObj != NULL)
			{
				(*m_audioPlayerObj)->Destroy(m_audioPlayerObj);
				m_audioPlayerObj = NULL;
				m_audioPlayer = NULL;
			}
		}

		ReturnValue AudioPlayer::Start()
		{
			SLresult res = (*m_audioPlayer)->SetPlayState(m_audioPlayer,SL_PLAYSTATE_STOPPED);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Start() error at SL_PLAYSTATE_STOPPED: res = %d",res);
				return RETURN_VALUE_KO;
			}
			res = (*m_audioPlayer)->SetPlayState(m_audioPlayer,SL_PLAYSTATE_PLAYING);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Start() error at SL_PLAYSTATE_PLAYING: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue AudioPlayer::Resume()
		{
			SLresult res = (*m_audioPlayer)->SetPlayState(m_audioPlayer,SL_PLAYSTATE_PLAYING);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Resume() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue AudioPlayer::Pause()
		{
			SLresult res = (*m_audioPlayer)->SetPlayState(m_audioPlayer,SL_PLAYSTATE_PAUSED);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Pause() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue AudioPlayer::Stop()
		{
			SLresult res = (*m_audioPlayer)->SetPlayState(m_audioPlayer,SL_PLAYSTATE_STOPPED);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Stop() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}
	}
}
