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

			/*
			struct SLVolumeItf_ {
			SLresult (*SetVolumeLevel) (
			SLVolumeItf self,
			SLmillibel level
			);
			SLresult (*GetVolumeLevel) (
			SLVolumeItf self,
			SLmillibel *pLevel
			);
			SLresult (*GetMaxVolumeLevel) (
			SLVolumeItf self,
			SLmillibel *pMaxLevel
			);

			SLresult (*EnableStereoPosition) (
			SLVolumeItf self,
			SLboolean enable
			);
			SLresult (*IsEnabledStereoPosition) (
			SLVolumeItf self,
			SLboolean *pEnable
			);OpenSL ES 1.0.1 Specification
			SLresult (*SetStereoPosition) (
			SLVolumeItf self,
			SLpermille stereoPosition
			);
			SLresult (*GetStereoPosition) (
			SLVolumeItf self,
			SLpermille *pStereoPosition
			);
			}; */

			bool IsMuted() const;
			Core::ReturnValue ToggleMute();
			Core::ReturnValue Mute();
			Core::ReturnValue Unmute();
			Core::ReturnValue SetMute(SLboolean mute);

		private:
			std::string m_path;

			SLObjectItf m_audioPlayerObj;
			SLPlayItf m_audioPlayer;
			SLVolumeItf m_audioVolume;

			bool m_muted;
		};
	}
}

#endif
