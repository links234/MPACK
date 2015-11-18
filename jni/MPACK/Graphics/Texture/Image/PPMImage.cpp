#include "PNGImage.hpp"

#include <png.h>

#include "Image.hpp"
#include "Resources.hpp"
#include "Misc.hpp"
#include "Log.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		ReturnValue LoadPPM(Image *image, const std::string &path, bool flipForOpenGL)
		{
			LOGE("LoadPPM() error: not implemented");
			return RETURN_VALUE_KO;
		}

		ReturnValue SavePPM(Image *image, const std::string &path)
		{
			LOGE("SavePPM() error: not implemented");
			return RETURN_VALUE_KO;
		}
	}
}
