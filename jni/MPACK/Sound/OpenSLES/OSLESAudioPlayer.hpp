#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESAUDIOPLAYER_HPP
#define MPACK_OSLESAUDIOPLAYER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PlayController;
		class VolumeController;
		class BassBoostController;
		class PlaybackRateController;
		class PitchController;
		class SeekController;

		class GroupController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class AudioPlayer
		{
		public:
			AudioPlayer();
			~AudioPlayer();

			std::string GetPath() const;

			Core::ReturnValue LoadFD(std::string path);
			void Unload();

			void AddToGroup(GroupController *pGroupController);
			void AddToGroup(std::string name);

			PlayController* 		Play() const;
			VolumeController* 		Volume() const;
			BassBoostController* 	BassBoost() const;
			PlaybackRateController* PlaybackRate() const;
			PitchController* 		Pitch() const;
			SeekController* 		Seek() const;

			static void Cleanup();
		private:
			Core::ReturnValue LoadControllers();

			std::string m_path;

			SLObjectItf m_audioPlayerObj;

			PlayController *m_pPlayController;
			VolumeController *m_pVolumeController;
			BassBoostController *m_pBassBoostController;
			PlaybackRateController *m_pPlaybackRateController;
			PitchController *m_pPitchController;
			SeekController *m_pSeekController;

			static std::unordered_set<AudioPlayer*> s_objects;
		};
	}
}

#endif

#endif
