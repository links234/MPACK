#ifndef INPUTSERVICE_HPP
#define INPUTSERVICE_HPP

#include "Platform.hpp"

#include "Android/AndroidInputService.hpp"
#include "Windows/WindowsInputService.hpp"

namespace Core
{
	struct Finger
	{
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
#elif	WINDOWS_PLATFORM
	typedef	 WindowsInputService	InputService;
#endif
}

#endif
