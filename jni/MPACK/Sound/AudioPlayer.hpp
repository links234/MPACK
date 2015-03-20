#ifndef MPACK_AUDIOPLAYER_HPP
#define MPACK_AUDIOPLAYER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class BassBoostController;
		class PlaybackRateController;
		class PitchController;
		class SeekController;
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

			Core::ReturnValue Load(std::string path);
			void Unload();

			Core::ReturnValue Start();
			Core::ReturnValue Resume();
			Core::ReturnValue Pause();
			Core::ReturnValue Stop();

			SLmillisecond GetPosition();
			SLmillisecond GetDuration();

			bool IsMuted() const;
			Core::ReturnValue ToggleMute();
			Core::ReturnValue Mute();
			Core::ReturnValue Unmute();
			Core::ReturnValue SetMute(SLboolean mute);

			Core::ReturnValue SetVolume(double linear);
			double GetVolume() const;

			bool IsStereoEnabled() const;
			Core::ReturnValue EnableStereo();
			Core::ReturnValue DisableStereo();
			Core::ReturnValue ToggleStereo();
			Core::ReturnValue SetEnableStereo(bool enabled);
			Core::ReturnValue SetStereoPosition(SLpermille stereoPosition);
			SLpermille GetStereoPosition() const;

			BassBoostController* 	BassBoost() const;
			PlaybackRateController* PlaybackRate() const;
			PitchController* 		Pitch() const;
			SeekController* 		Seek() const;

		private:
			std::string m_path;

			SLObjectItf m_audioPlayerObj;
			SLPlayItf m_audioPlayer;
			SLVolumeItf m_audioVolume;

			bool m_muted;
			double m_volume;
			SLmillibel m_mBMinVolume;
			SLmillibel m_mBMaxVolume;

			bool m_stereoEnabled;
			SLpermille m_stereoPosition;

			BassBoostController *m_pBassBoostController;

			PlaybackRateController *m_pPlaybackRateController;

			PitchController *m_pPitchController;

			SeekController *m_pSeekController;
		};
	}
}

#endif
