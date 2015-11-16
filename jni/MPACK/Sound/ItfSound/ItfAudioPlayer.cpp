#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "Types.hpp"
#include "Resources.hpp"
#include "Log.hpp"

#include "ItfAudioPlayer.hpp"

#include "ItfSoundService.hpp"
#include "ItfAudioControllers.hpp"
#include "ItfGroupControllers.hpp"
#include "ItfOutputMixer.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		unordered_set<AudioPlayer*> AudioPlayer::s_objects;

		AudioPlayer::AudioPlayer()
			: m_path(),
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

			LoadControllers();

			m_path=path;
			return RETURN_VALUE_OK;
		}

		void AudioPlayer::Unload()
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
			m_path = "";
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
			m_pPlayController = new PlayController();
			m_pVolumeController = new VolumeController();
			m_pBassBoostController = new BassBoostController();
			m_pPlaybackRateController = new PlaybackRateController();
			m_pPitchController = new PitchController();
			m_pSeekController = new SeekController();

			return RETURN_VALUE_OK;
		}
	}
}

#endif
