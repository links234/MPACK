#ifndef MPACK_INPUTSERVICE_HPP
#define MPACK_INPUTSERVICE_HPP

#include "Types.hpp"
#include "Android/AndroidInputService.hpp"
#include "Windows/WindowsInputService.hpp"
#include "Linux/LinuxInputService.hpp"
#include "OSX/OSXInputService.hpp"

namespace MPACK
{
	namespace Input
	{
		class Finger
		{
		public:
			enum Flag
			{
				FREE,
				LOCKED
			};

			GLuint 			m_id;
			Flag 			m_flag;
			Math::Vector2f 	m_pos;
		};

	#if defined(ANDROID_PLATFORM)
		typedef	 AndroidInputService	InputService;
	#elif	defined(WINDOWS_PLATFORM)
		typedef	 WindowsInputService	InputService;
	#elif	defined(LINUX_PLATFORM)
		typedef LinuxInputService		InputService;
	#elif defined(OSX_PLATFORM)
		typedef OSXInputService	InputService;
	#endif
	}
}

#endif
