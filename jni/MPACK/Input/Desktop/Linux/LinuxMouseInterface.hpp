#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXMOUSEINTERFACE_HPP
#define MPACK_LINUXMOUSEINTERFACE_HPP

#include "MouseInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		class LinuxMouseInterface : public MouseInterface
		{
		public:
			LinuxMouseInterface();
			~LinuxMouseInterface();

			void Update();
		};
	}
}

#endif

#endif
