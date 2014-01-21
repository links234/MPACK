#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MOUSEINTERFACE_HPP
#define MOUSEINTERFACE_HPP

#include "Types.hpp"
#include "Maths.hpp"

namespace Core
{
	class MouseInterface
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

		bool operator!= (const MouseInterface &other);
		bool operator== (const MouseInterface &other);
	};
}

#endif

#endif
