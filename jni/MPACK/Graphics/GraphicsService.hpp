#ifndef MPACK_GRAPHICSSERVICE_HPP
#define MPACK_GRAPHICSSERVICE_HPP

#include "Types.hpp"
#include "CursorDrawer.hpp"
#include "PostEffect.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class GraphicsService
		{
		public:
			GraphicsService();
			~GraphicsService();

			Core::ReturnValue Start();
			void Stop();

			void Update(GLfloat delta);
			Core::ReturnValue Render();

		protected:
			Core::ReturnValue LoadResources();
			Core::ReturnValue UnloadResources();
		};
	}
}

#endif
