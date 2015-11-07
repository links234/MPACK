#ifndef MPACK_PPMIMAGE_HPP
#define MPACK_PPMIMAGE_HPP

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
		Core::ReturnValue LoadPPM(Image *image, const std::string &path);
		Core::ReturnValue SavePPM(Image *image, const std::string &path);
	}
}

#endif
