#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_MOUSESTATE_HPP
#define MPACK_MOUSESTATE_HPP

#include "Types.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Input
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
}

#endif

#endif
