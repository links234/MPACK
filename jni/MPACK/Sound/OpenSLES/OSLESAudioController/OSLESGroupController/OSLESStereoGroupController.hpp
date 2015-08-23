#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESSTEREOGROUPCONTROLLER_HPP
#define MPACK_OSLESSTEREOGROuPCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class GroupController;
		class VolumeGroupController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class StereoGroupController
		{
		public:
			~StereoGroupController();

			Core::ReturnValue Enable();
			Core::ReturnValue Disable();
			Core::ReturnValue Toggle();
			Core::ReturnValue SetEnabled(bool enabled);
			Core::ReturnValue Set(SLpermille position);

		private:
			StereoGroupController(GroupController *pGroupController);

			GroupController *m_pGroupController;

			friend class VolumeGroupController;
		};
	}
}

#endif

#endif
