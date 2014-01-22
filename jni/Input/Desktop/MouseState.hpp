#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MOUSESTATE_HPP
#define MOUSESTATE_HPP

#include "Types.hpp"
#include "Maths.hpp"

namespace Core
{
	class MouseState
	{
	public:
		class Buttons
		{
		public:
			bool Left,Right,Middle;

			bool operator!= (const Buttons &other) const;
			bool operator== (const Buttons &other) const;
		};

		Buttons			Button;
		Math::Vector2f	Pos;
		GLuint			Wheel;

		bool operator!= (const MouseState &other) const;
		bool operator== (const MouseState &other) const;
	};
}

#endif

#endif
