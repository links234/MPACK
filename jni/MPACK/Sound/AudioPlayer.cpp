#include "AudioPlayer.hpp"

#include "SoundService.hpp"
#include "Global.hpp"
#include "Context.hpp"
#include "OutputMixer.hpp"
#include "Math.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		AudioPlayer::AudioPlayer()
			: m_path(), m_audioPlayerObj(NULL), m_audioPlayer(NULL), m_audioVolume(NULL),
			  m_muted(false), m_volume(1.0), m_mBMinVolume(0), m_mBMaxVolume(0),
			  m_stereoEnabled(false), m_stereoPosition(0),
			  m_audioBassBoost(NULL), m_bassBoostEnabled(false), m_bassBoostStrength(0)
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

			const SLuint32 audioPlayerIIDCount = 2;
			const SLInterfaceID audioPlayerIIDs[] =	{ SL_IID_PLAY, SL_IID_VOLUME, SL_IID_BASSBOOST };
			const SLboolean audioPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

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
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->GetInterface(SL_IID_PLAY)");
				goto ERROR;
			}

			res = (*m_audioPlayerObj)->GetInterface(m_audioPlayerObj, SL_IID_VOLUME, &m_audioVolume);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->GetInterface(SL_IID_VOLUME)");
				goto ERROR;
			}

			m_mBMinVolume = SL_MILLIBEL_MIN;
			m_mBMaxVolume = SL_MILLIBEL_MIN;
			res = (*m_audioVolume)->GetMaxVolumeLevel(m_audioVolume, &m_mBMaxVolume);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioVolume)->GetMaxVolumeLevel");
				goto ERROR;
			}

			res = (*m_audioPlayerObj)->GetInterface(m_audioPlayerObj, SL_IID_BASSBOOST, &m_audioBassBoost);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->GetInterface(SL_IID_BASSBOOST)");
				LOGE("AudioPlayer::Load(): Bass boost is not supported!");
				m_audioBassBoost=NULL;
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
				m_audioVolume = NULL;
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

		bool AudioPlayer::IsMuted() const
		{
			return m_muted;
		}

		Core::ReturnValue AudioPlayer::ToggleMute()
		{
			return SetMute(!m_muted);
		}

		Core::ReturnValue AudioPlayer::Mute()
		{
			return SetMute(true);
		}

		Core::ReturnValue AudioPlayer::Unmute()
		{
			return SetMute(false);
		}

		ReturnValue AudioPlayer::SetMute(SLboolean mute)
		{
			SLresult res = (*m_audioVolume)->SetMute(m_audioVolume,mute);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetMute() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_muted=mute;
			return RETURN_VALUE_OK;
		}

		Core::ReturnValue AudioPlayer::SetVolume(double linear)
		{
			int dBVolume = 20*log10(linear);
			SLmillibel mBVolume = dBVolume*100;

			mBVolume = Math::Misc<SLmillibel>::Clamp(mBVolume,m_mBMinVolume,m_mBMaxVolume);

			SLresult res = (*m_audioVolume)->SetVolumeLevel(m_audioVolume, mBVolume);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetVolume() error: res = %d",res);
				return RETURN_VALUE_KO;
			}

			m_volume=linear;
			return RETURN_VALUE_OK;
		}

		double AudioPlayer::GetVolume() const
		{
			return m_volume;
		}

		bool AudioPlayer::IsStereoEnabled() const
		{
			return m_stereoEnabled;
		}

		Core::ReturnValue AudioPlayer::EnableStereo()
		{
			return SetEnableStereo(true);
		}

		Core::ReturnValue AudioPlayer::DisableStereo()
		{
			return SetEnableStereo(false);
		}

		Core::ReturnValue AudioPlayer::ToggleStereo()
		{
			return SetEnableStereo(!m_stereoEnabled);
		}

		Core::ReturnValue AudioPlayer::SetEnableStereo(bool enabled)
		{
			SLresult res = (*m_audioVolume)->EnableStereoPosition(m_audioVolume, enabled);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetEnableStereo() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_stereoEnabled=enabled;
			return RETURN_VALUE_OK;
		}

		Core::ReturnValue AudioPlayer::SetStereoPosition(SLpermille stereoPosition)
		{
			SLresult res = (*m_audioVolume)->SetStereoPosition(m_audioVolume, stereoPosition);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetStereoPosition() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_stereoPosition=stereoPosition;
			return RETURN_VALUE_OK;
		}

		SLpermille AudioPlayer::GetStereoPosition() const
		{
			return m_stereoPosition;
		}

		bool AudioPlayer::IsBassBostEnabled() const
		{
			return m_bassBoostEnabled;
		}

		Core::ReturnValue AudioPlayer::EnableBassBoost()
		{
			return SetEnableBassBoost(true);
		}

		Core::ReturnValue AudioPlayer::DisableBassBoost()
		{
			return SetEnableBassBoost(false);
		}

		Core::ReturnValue AudioPlayer::ToggleBassBoost()
		{
			return SetEnableBassBoost(!m_bassBoostEnabled);
		}

		Core::ReturnValue AudioPlayer::SetEnableBassBoost(bool enabled)
		{
			SLresult res = (*m_audioBassBoost)->SetEnabled(m_audioBassBoost, enabled);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetEnableBassBoost() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_bassBoostEnabled=enabled;
			return RETURN_VALUE_OK;
		}

		Core::ReturnValue AudioPlayer::SetBassBoostStrength(SLpermille bassBoostStrength)
		{
			SLresult res = (*m_audioBassBoost)->SetStrength(m_audioBassBoost, bassBoostStrength);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetBassBoostStrength() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_bassBoostStrength=bassBoostStrength;
			return RETURN_VALUE_OK;
		}

		SLpermille AudioPlayer::GetBassBoostStrength() const
		{
			return m_bassBoostStrength;
		}
	}
}
