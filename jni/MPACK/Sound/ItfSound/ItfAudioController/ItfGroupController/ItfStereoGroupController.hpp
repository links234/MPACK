#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFSTEREOGROUPCONTROLLER_HPP
#define MPACK_ITFSTEREOGROuPCONTROLLER_HPP

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
			Core::ReturnValue Set(int position);

		private:
			StereoGroupController(GroupController *pGroupController);

			GroupController *m_pGroupController;

			friend class VolumeGroupController;
		};
	}
}

#endif

#endif
