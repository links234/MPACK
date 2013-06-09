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
        void Setup(int width, int height);
        void Stop();

        void Update();
        Status Render();

	protected:
		Status LoadResources();
		Status UnloadResources();

    private:
        // Display properties.
        EGLDisplay mDisplay;
        EGLSurface mSurface;
        EGLContext mContext;
    };
}
#endif
