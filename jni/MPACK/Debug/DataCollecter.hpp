#ifndef MPACK_DATACOLLECTER_HPP
#define MPACK_DATACOLLECTER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Texture2D;
	}
}

namespace MPACK
{
	namespace Profiler
	{
		void RegisterCall_SpriteRender(Graphics::Texture2D *pTexture,
				 	 	 	 	 	   double x, double y, double width, double height,
									   double minU, double maxU, double minV, double maxV);

		void GenerateMTexResizeJSON(std::string path);
	}
}

#endif
