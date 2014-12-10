#ifndef MPACK_GRAPHICSSERVICE_HPP
#define MPACK_GRAPHICSSERVICE_HPP

#include "Types.hpp"
#include "CursorDrawer.hpp"
#include "PostEffect.hpp"

namespace Core
{
    class GraphicsService
    {
    public:
        GraphicsService();

        ReturnValue Start();
        void Stop();

        void Update(GLfloat delta);
        ReturnValue Render();

	protected:
        ReturnValue LoadResources();
        ReturnValue UnloadResources();
    };
}
#endif
