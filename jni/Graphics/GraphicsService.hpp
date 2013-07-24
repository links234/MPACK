#ifndef GRAPHICSSERVICE_HPP
#define GRAPHICSSERVICE_HPP

#include "Types.hpp"

namespace Core
{
    class GraphicsService
    {
    public:
        GraphicsService();

        Status Start();
        void Stop();

        void Update(GLfloat delta);
        Status Render();

	protected:
		Status LoadResources();
		Status UnloadResources();
    };
}
#endif
