#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESVOLUMECONTROLLER_HPP
#define MPACK_OSLESVOLUMECONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class StereoController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class VolumeController
		{
		public:
			VolumeController(SLObjectItf object);
			~VolumeController();

			bool IsSupported() const;

			bool IsMuted() const;
			Core::ReturnValue ToggleMute();
			Core::ReturnValue Mute();
			Core::ReturnValue Unmute();
			Core::ReturnValue SetMute(SLboolean mute);

			Core::ReturnValue Set(double linear);
			double Get() const;

			StereoController* Stereo() const;

			static VolumeController* GetSentinel();

		private:
			VolumeController();

			Core::ReturnValue SetEnabledStereo(bool enabled);
			Core::ReturnValue SetStereoPosition(SLpermille stereoPosition);

			SLVolumeItf m_interface;

			bool m_muted;
			double m_volume;
			SLmillibel m_mBMinVolume;
			SLmillibel m_mBMaxVolume;

			StereoController *m_pStereoController;

			static VolumeController s_sentinel;

			friend class StereoController;
		};
	}
}

#endif

#endif
