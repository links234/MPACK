#ifdef ANDROID_PLATFORM

#include "OSLESAudioPlayer.hpp"

#include "OSLESSoundService.hpp"
#include "OSLESAudioControllers.hpp"
#include "OSLESGroupControllers.hpp"
#include "OSLESOutputMixer.hpp"
#include "Resources.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "Math.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		unordered_set<AudioPlayer*> AudioPlayer::s_objects;

		AudioPlayer::AudioPlayer()
			: m_path(), m_audioPlayerObj(NULL),
			  m_pPlayController(PlayController::GetSentinel()),
			  m_pVolumeController(VolumeController::GetSentinel()),
			  m_pBassBoostController(BassBoostController::GetSentinel()),
			  m_pPlaybackRateController(PlaybackRateController::GetSentinel()),
			  m_pPitchController(PitchController::GetSentinel()),
			  m_pSeekController(SeekController::GetSentinel())
		{
			s_objects.insert(this);
		}

		AudioPlayer::~AudioPlayer()
		{
			s_objects.erase(this);
			Unload();
		}

		string AudioPlayer::GetPath() const
		{
			return m_path;
		}

		ReturnValue AudioPlayer::LoadFD(string path)
		{
			Unload();

			string realPath=GetInputResourcePath(path);

			SLEngineItf &engine=Global::pContext->pSoundService->GetOpenSLEngine();

			AAsset* asset = AAssetManager_open(pAAssetManager, realPath.c_str(), AASSET_MODE_UNKNOWN);

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

			if(LoadControllers()==RETURN_VALUE_KO)
			{
				LOGE("AudioPlater::Load() failed to LoadControllers()");
				goto ERROR;
			}

			m_path=path;
			return RETURN_VALUE_OK;

		ERROR:
			LOGE("AudioPlayer()::Load(\"%s\") failed ",path.c_str(),res);
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
				if(m_pVolumeController!=VolumeController::GetSentinel())
				{
					delete m_pVolumeController;
					m_pVolumeController=VolumeController::GetSentinel();
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

		void AudioPlayer::AddToGroup(GroupController *pGroupController)
		{
			pGroupController->Add(this);
		}

		void AudioPlayer::AddToGroup(std::string name)
		{
			GroupController::Get(name)->Add(this);
		}

		PlayController* AudioPlayer::Play() const
		{
			return m_pPlayController;
		}

		VolumeController *AudioPlayer::Volume() const
		{
			return m_pVolumeController;
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

		void AudioPlayer::Cleanup()
		{
			vector<AudioPlayer*> allObjects;
			for(unordered_set<AudioPlayer*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
			{
				allObjects.push_back(*it);
			}
			s_objects.clear();
			for(vector<AudioPlayer*>::iterator it=allObjects.begin();it!=allObjects.end();++it)
			{
				delete (*it);
			}
		}

		Core::ReturnValue AudioPlayer::LoadControllers()
		{
			m_pPlayController = new PlayController(m_audioPlayerObj);
			if(!m_pPlayController->IsSupported())
			{
				LOGE("AudioPlayer::LoadControllers(): PlayController() failed");
				goto ERROR;
			}

			m_pVolumeController = new VolumeController(m_audioPlayerObj);
			if(!m_pVolumeController->IsSupported())
			{
				LOGE("AudioPlayer::LoadControllers(): VolumeController() failed");
				goto ERROR;
			}

			m_pBassBoostController = new BassBoostController(m_audioPlayerObj);
			m_pPlaybackRateController = new PlaybackRateController(m_audioPlayerObj);
			m_pPitchController = new PitchController(m_audioPlayerObj);
			m_pSeekController = new SeekController(m_audioPlayerObj);

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("AudioPlayer()::LoadControllers() failed");
			return RETURN_VALUE_KO;
		}
	}
}

#endif
