#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFSTEREOCONTROLLER_HPP
#define MPACK_ITFSTEREOCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class VolumeController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class StereoController
		{
		public:
			~StereoController();

			bool IsSupported() const;

			bool IsEnabled() const;
			Core::ReturnValue Enable();
			Core::ReturnValue Disable();
			Core::ReturnValue Toggle();
			Core::ReturnValue SetEnabled(bool enabled);
			Core::ReturnValue Set(int position);
			int Get() const;

			static StereoController* GetSentinel();

		protected:
			StereoController(VolumeController *pVolumeController);

			VolumeController *m_pVolumeController;

			bool m_enabled;
			int m_position;

			static StereoController s_sentinel;

			friend class VolumeController;
		};
	}
}

#endif

#endif
