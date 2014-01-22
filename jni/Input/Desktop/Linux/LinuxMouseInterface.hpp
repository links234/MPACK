#ifdef LINUX_PLATFORM

#ifndef LINUXMOUSEINTERFACE_HPP
#define LINUXMOUSEINTERFACE_HPP

#include "MouseInterface.hpp"

namespace Core
{
	class LinuxMouseInterface : public MouseInterface
	{
	public:
		LinuxMouseInterface();
		~LinuxMouseInterface();

		void Update();
	};
}

#endif

#endif
