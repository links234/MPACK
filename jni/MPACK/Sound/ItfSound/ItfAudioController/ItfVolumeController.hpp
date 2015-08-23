#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFVOLUMECONTROLLER_HPP
#define MPACK_ITFVOLUMECONTROLLER_HPP

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
			VolumeController();
			~VolumeController();

			bool IsSupported() const;

			bool IsMuted() const;
			Core::ReturnValue ToggleMute();
			Core::ReturnValue Mute();
			Core::ReturnValue Unmute();
			Core::ReturnValue SetMute(bool mute);

			Core::ReturnValue Set(double linear);
			double Get() const;

			StereoController* Stereo() const;

			static VolumeController* GetSentinel();

		private:
			Core::ReturnValue SetEnabledStereo(bool enabled);
			Core::ReturnValue SetStereoPosition(int stereoPosition);

			StereoController *m_pStereoController;
			bool m_muted;
			double m_volume;

			static VolumeController s_sentinel;

			friend class StereoController;
		};
	}
}

#endif

#endif
