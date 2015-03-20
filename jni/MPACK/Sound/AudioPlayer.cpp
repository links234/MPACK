#include "AudioPlayer.hpp"

#include "SoundService.hpp"
#include "OutputMixer.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "Math.hpp"

#include "BassBoostController.hpp"
#include "SeekController.hpp"

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
			  m_stereoEnabled(false), m_stereoPosition(0), m_pBassBoostController(BassBoostController::GetSentinel()),
			  m_audioPlaybackRate(NULL), m_playbackRate(1.0), m_minPlaybackRate(1.0), m_maxPlaybackRate(1.0),
			  m_audioPitch(NULL), m_pitch(1000), m_minPitch(1000), m_maxPitch(1000),
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

			m_pBassBoostController = new BassBoostController(m_audioPlayerObj);

			res = (*m_audioPlayerObj)->GetInterface(m_audioPlayerObj, SL_IID_PLAYBACKRATE, &m_audioPlaybackRate);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->GetInterface(SL_IID_PLAYBACKRATE)");
				LOGE("AudioPlayer::Load(): PlaybackRateItf is not supported: res = %d",res);
				m_audioPlaybackRate=NULL;
			}
			else
			{
				m_minPlaybackRate=0.5;
				m_maxPlaybackRate=2.0;

				res = (*m_audioPlaybackRate)->SetPropertyConstraints(m_audioPlaybackRate, SL_RATEPROP_NOPITCHCORAUDIO);
				if(res != SL_RESULT_SUCCESS)
				{
					LOGE("AudioPlayer::Load() at (*m_audioPlaybackRate)->SetPropertyConstraints");
				}
			}

			res = (*m_audioPlayerObj)->GetInterface(m_audioPlayerObj, SL_IID_PITCH, &m_audioPitch);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::Load() at (*m_audioPlayerObj)->GetInterface(SL_IID_PITCH)");
				LOGE("AudioPlayer::Load(): PitchItf is not supported: res = %d",res);
				m_audioPitch=NULL;
			}
			else
			{
				SLresult res = (*m_audioPitch)->GetPitchCapabilities(m_audioPitch, &m_minPitch, &m_maxPitch);
				if (res == SL_RESULT_SUCCESS)
				{
					LOGE("AudioPlayer::Load() at (*m_audioPlaybackRate)->GetPitchCapabilities");
				}
			}

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
				if(m_pBassBoostController!=BassBoostController::GetSentinel())
				{
					delete m_pBassBoostController;
					m_pBassBoostController=BassBoostController::GetSentinel();
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

		SLmillisecond AudioPlayer::GetPosition()
		{
			SLmillisecond position;
			SLresult res = (*m_audioPlayer)->GetPosition(m_audioPlayer, &position);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::GetPosition() error: res = %d",res);
				return 0;
			}
			return position;
		}

		SLmillisecond AudioPlayer::GetDuration()
		{
			SLmillisecond duration;
			SLresult res = (*m_audioPlayer)->GetDuration(m_audioPlayer, &duration);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::GetDuration() error: res = %d",res);
				return 0;
			}
			return duration;
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

		ReturnValue AudioPlayer::SetPlaybackRate(double rate)
		{
			rate = Math::Misc<double>::Clamp(rate,m_minPlaybackRate,m_maxPlaybackRate);

			SLresult res = (*m_audioPlaybackRate)->SetRate(m_audioPlaybackRate, (SLpermille)(rate*1000));
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetPlaybackRate() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_playbackRate=rate;
			return RETURN_VALUE_OK;
		}

		double AudioPlayer::GetPlaybackRate() const
		{
			return m_playbackRate;
		}

		ReturnValue AudioPlayer::SetPitch(SLpermille pitch)
		{
			pitch=Math::Misc<SLpermille>::Clamp(pitch,m_minPitch,m_maxPitch);
			SLresult res = (*m_audioPitch)->SetPitch(m_audioPitch, pitch);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetPitch() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_pitch=pitch;
			return RETURN_VALUE_OK;
		}

		SLpermille AudioPlayer::GetPitch() const
		{
			return m_pitch;
		}

		SeekController* AudioPlayer::Seek() const
		{
			return m_pSeekController;
		}
	}
}
