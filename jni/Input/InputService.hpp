#ifndef INPUTSERVICE_HPP
#define INPUTSERVICE_HPP

#include "Platform.hpp"

#include "AndroidInputService.hpp"
#include "WindowsInputService.hpp"

namespace Core
{
	struct Finger
	{
		enum Flag
		{
			FREE,
			LOCKED
		};

		GLuint 		m_id;
		Flag 		m_flag;
		Vector2f 	m_pos;
	};

#ifdef ANDROID_PLATFORM
	typedef	 AndroidInputService	InputService;
#elif	WINDOWS_PLATFORM
	typedef	 WindowsInputService	InputService;
#endif
}

#endif
