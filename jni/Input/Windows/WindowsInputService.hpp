#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSINPUTSERVICE_HPP
#define WINDOWSINPUTSERVICE_HPP


namespace Core
{
	struct Finger;

	class WindowsInputService
	{
	public:
		WindowsInputService();
		~WindowsInputService();
	};
}

#endif

#endif
