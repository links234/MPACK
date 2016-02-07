#ifndef MPACK_PNGIMAGE_HPP
#define MPACK_PNGIMAGE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Image;
	}
}

namespace MPACK
{
	namespace Graphics
	{
		Core::ReturnValue LoadPNG(Image *image, const std::string &path, bool flipForOpenGL = true);
		Core::ReturnValue SavePNG(Image *image, const std::string &path);
	}
}

#endif
