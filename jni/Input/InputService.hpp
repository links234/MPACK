#ifndef INPUTSERVICE_HPP
#define INPUTSERVICE_HPP

#include "Platform.hpp"

#include "Types.hpp"
#include "Android/AndroidInputService.hpp"
#include "Windows/WindowsInputService.hpp"

namespace Core
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

#ifdef ANDROID_PLATFORM
	typedef	 AndroidInputService	InputService;
#elif	defined(WINDOWS_PLATFORM)
	typedef	 WindowsInputService	InputService;
#endif
}

#endif
