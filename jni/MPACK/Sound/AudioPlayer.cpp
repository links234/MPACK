#include "AudioPlayer.hpp"

#include "SoundService.hpp"
#include "OutputMixer.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "Math.hpp"

#include "PlayController.hpp"
#include "BassBoostController.hpp"
#include "PitchController.hpp"
#include "PlaybackRateController.hpp"
#include "SeekController.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		AudioPlayer::AudioPlayer()
			: m_path(), m_audioPlayerObj(NULL),
			  m_pPlayController(PlayController::GetSentinel()),
			  m_audioVolume(NULL),
			  m_muted(false), m_volume(1.0), m_mBMinVolume(0), m_mBMaxVolume(0),
			  m_stereoEnabled(false), m_stereoPosition(0),
			  m_pBassBoostController(BassBoostController::GetSentinel()),
			  m_pPlaybackRateController(PlaybackRateController::GetSentinel()),
			  m_pPitchController(PitchController::GetSentinel()),
			  m_pSeekController(SeekController::GetSentinel())
		{
		}

		AudioPlayer::~AudioPlayer()
		{
			Unload();
		}

		string AudioPlayer::GetPath() const
		{
			return m_path;
		}

		ReturnValue AudioPlayer::Load(string path)
		{
			Unload();

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

			const SLuint32 audioPlayerIIDCount = 10;
			SLInterfaceID audioPlayerIIDs[audioPlayerIIDCount];
			SLboolean audioPlayerReqs[audioPlayerIIDCount];
			for(int indexIID=0;indexIID<audioPlayerIIDCount;++indexIID)
			{
				audioPlayerIIDs[indexIID]=SL_IID_NULL;
				audioPlayerReqs[indexIID]=SL_BOOLEAN_FALSE;
			}
			audioPlayerIIDs[0]=SL_IID_PLAY;
			audioPlayerReqs[0]=SL_BOOLEAN_TRUE;
			audioPlayerIIDs[1]=SL_IID_VOLUME;
			audioPlayerReqs[1]=SL_BOOLEAN_TRUE;
			audioPlayerIIDs[2]=SL_IID_BASSBOOST;
			audioPlayerReqs[2]=SL_BOOLEAN_FALSE;
			audioPlayerIIDs[3]=SL_IID_PLAYBACKRATE;
			audioPlayerReqs[3]=SL_BOOLEAN_FALSE;
			audioPlayerIIDs[4]=SL_IID_PITCH;
			audioPlayerReqs[4]=SL_BOOLEAN_FALSE;
			audioPlayerIIDs[5]=SL_IID_SEEK;
			audioPlayerReqs[5]=SL_BOOLEAN_FALSE;

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

			m_pPlayController = new PlayController(m_audioPlayerObj);

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

			m_pBassBoostController = new BassBoostController(m_audioPlayerObj);

			m_pPlaybackRateController = new PlaybackRateController(m_audioPlayerObj);

			m_pPitchController = new PitchController(m_audioPlayerObj);

			m_pSeekController = new SeekController(m_audioPlayerObj);

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
				if(m_pPlayController!=PlayController::GetSentinel())
				{
					delete m_pPlayController;
					m_pPlayController=PlayController::GetSentinel();
				}
				if(m_pBassBoostController!=BassBoostController::GetSentinel())
				{
					delete m_pBassBoostController;
					m_pBassBoostController=BassBoostController::GetSentinel();
				}
				if(m_pPlaybackRateController!=PlaybackRateController::GetSentinel())
				{
					delete m_pPlaybackRateController;
					m_pPlaybackRateController=PlaybackRateController::GetSentinel();
				}
				if(m_pPitchController!=PitchController::GetSentinel())
				{
					delete m_pPitchController;
					m_pPitchController=PitchController::GetSentinel();
				}
				if(m_pSeekController!=SeekController::GetSentinel())
				{
					delete m_pSeekController;
					m_pSeekController=SeekController::GetSentinel();
				}
				(*m_audioPlayerObj)->Destroy(m_audioPlayerObj);
				m_audioPlayerObj = NULL;
				m_path = "";
			}
		}

		PlayController* AudioPlayer::Play() const
		{
			return m_pPlayController;
		}

		bool AudioPlayer::IsMuted() const
		{
			return m_muted;
		}

		ReturnValue AudioPlayer::ToggleMute()
		{
			return SetMute(!m_muted);
		}

		ReturnValue AudioPlayer::Mute()
		{
			return SetMute(true);
		}

		ReturnValue AudioPlayer::Unmute()
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

		ReturnValue AudioPlayer::SetVolume(double linear)
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

		ReturnValue AudioPlayer::EnableStereo()
		{
			return SetEnableStereo(true);
		}

		ReturnValue AudioPlayer::DisableStereo()
		{
			return SetEnableStereo(false);
		}

		ReturnValue AudioPlayer::ToggleStereo()
		{
			return SetEnableStereo(!m_stereoEnabled);
		}

		ReturnValue AudioPlayer::SetEnableStereo(bool enabled)
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

		ReturnValue AudioPlayer::SetStereoPosition(SLpermille stereoPosition)
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

		BassBoostController* AudioPlayer::BassBoost() const
		{
			return m_pBassBoostController;
		}

		PlaybackRateController* AudioPlayer::PlaybackRate() const
		{
			return m_pPlaybackRateController;
		}

		PitchController* AudioPlayer::Pitch() const
		{
			return m_pPitchController;
		}

		SeekController* AudioPlayer::Seek() const
		{
			return m_pSeekController;
		}
	}
}
