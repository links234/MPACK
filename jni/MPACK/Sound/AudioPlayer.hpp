#ifndef MPACK_AUDIOPLAYER_HPP
#define MPACK_AUDIOPLAYER_HPP

#include "Types.hpp"

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

			bool IsBassBostEnabled() const;
			Core::ReturnValue EnableBassBoost();
			Core::ReturnValue DisableBassBoost();
			Core::ReturnValue ToggleBassBoost();
			Core::ReturnValue SetEnableBassBoost(bool enabled);
			Core::ReturnValue SetBassBoostStrength(SLpermille bassBoostStrength);
			SLpermille GetBassBoostStrength() const;

			Core::ReturnValue SetPlaybackRate(double rate);
			double GetPlaybackRate() const;

			Core::ReturnValue SetPitch(SLpermille pitch);
			SLpermille GetPitch() const;

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

			SLBassBoostItf m_audioBassBoost;
			bool m_bassBoostEnabled;
			SLpermille m_bassBoostStrength;

			SLPlaybackRateItf m_audioPlaybackRate;
			double m_playbackRate;
			double m_minPlaybackRate;
			double m_maxPlaybackRate;

			SLPitchItf m_audioPitch;
			SLpermille m_minPitch;
			SLpermille m_maxPitch;
			SLpermille m_pitch;
		};
	}
}

#endif
