#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSMOUSEINTERFACE_HPP
#define WINDOWSMOUSEINTERFACE_HPP

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
