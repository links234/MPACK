#ifdef WINDOWS_PLATFORM

#ifndef MPACK_WINDOWSMOUSEINTERFACE_HPP
#define MPACK_WINDOWSMOUSEINTERFACE_HPP

#include "MouseInterface.hpp"

namespace Core
{
	class WindowsMouseInterface : public MouseInterface
	{
	public:
		WindowsMouseInterface();
		~WindowsMouseInterface();

		void Update();
	};
}

#endif

#endif
