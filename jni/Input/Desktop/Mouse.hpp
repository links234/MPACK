#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Types.hpp"
#include "Maths.hpp"

namespace Core
{
	class Mouse
	{
	public:
		class Buttons
		{
		public:
			bool Left,Right,Middle;

			bool operator!= (const Buttons &other);
			bool operator== (const Buttons &other);
		};

		Buttons			Button;
		Math::Vector2f	Pos;
		GLuint			Wheel;

		bool operator!= (const Mouse &other);
		bool operator== (const Mouse &other);
	};
}

#endif

#endif
