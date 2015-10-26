#ifndef MPACK_COLOR_HPP
#define MPACK_COLOR_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Color
		{
		public:
			Color(BYTE r = 0, BYTE g = 0, BYTE b = 0, BYTE a = 0);

			BYTE r, g, b, a;
		};
	}
}

#endif
