#ifndef MPACK_RECT_HPP
#define MPACK_RECT_HPP

namespace MPACK
{
	namespace Graphics
	{
		class Rect
		{
		public:
			Rect(int x = 0, int y = 0, int width = 0, int height = 0);

			int x, y;
			int width, height;
		};
	}
}

#endif
