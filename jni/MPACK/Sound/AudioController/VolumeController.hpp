#ifndef MPACK_VOLUMECONTROLLER_HPP
#define MPACK_VOLUMECONTROLLER_HPP

#include "Types.hpp"

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

			bool IsStereoEnabled() const;
			Core::ReturnValue EnableStereo();
			Core::ReturnValue DisableStereo();
			Core::ReturnValue ToggleStereo();
			Core::ReturnValue SetEnabledStereo(bool enabled);
			Core::ReturnValue SetStereoPosition(SLpermille stereoPosition);
			SLpermille GetStereoPosition() const;

			static VolumeController* GetSentinel();

		private:
			VolumeController();

			SLVolumeItf m_interface;

			bool m_muted;
			double m_volume;
			SLmillibel m_mBMinVolume;
			SLmillibel m_mBMaxVolume;

			bool m_stereoEnabled;
			SLpermille m_stereoPosition;

			static VolumeController s_sentinel;
		};
	}
}

#endif
