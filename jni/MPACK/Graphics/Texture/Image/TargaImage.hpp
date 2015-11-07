#ifndef MPACK_TARGAIMAGE_HPP
#define MPACK_TARGAIMAGE_HPP

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
		Core::ReturnValue LoadTGA(Image *image, const std::string &path);
		Core::ReturnValue SaveTGA(Image *image, const std::string &path);
	}
}

#endif 
