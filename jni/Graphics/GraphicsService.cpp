#include "GraphicsService.hpp"

#include "Global.hpp"
#include "TimeService.hpp"
#include "Render.hpp"
#include "Texture2D.hpp"
#include "TextureMappedFont.hpp"
#include "Log.hpp"
#include "Particles.hpp"

namespace Core
{
    GraphicsService::GraphicsService() :
        mDisplay(EGL_NO_DISPLAY),
        mSurface(EGL_NO_CONTEXT),
        mContext(EGL_NO_SURFACE)
    {
    	LOGI("Creating GraphicsService.");
    }

    Status GraphicsService::Start()
    {
    	int mWidth(0),mHeight(0);

    	LOGI("Starting GraphicsService.");

        EGLint lFormat, lNumConfigs, lErrorResult;
        EGLConfig lConfig;
        // Defines display requirements. 16bits mode here.
        const EGLint lAttributes[] =
        	{
        		EGL_RENDERABLE_TYPE, EGL_WINDOW_BIT,
        		EGL_RED_SIZE, 8,
        		EGL_GREEN_SIZE, 8,
        		EGL_BLUE_SIZE, 8,
        		EGL_DEPTH_SIZE, 24,
        		EGL_NONE
        	};
        const EGLint lContextAttrib[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
		};

        // Retrieves a display connection and initializes it.
        LOGD("Connecting to the display.");
        mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (mDisplay == EGL_NO_DISPLAY)
        {
        	LOGE("EGL_NO_DISPLAY");
        	goto ERROR;
        }
        if (!eglInitialize(mDisplay, NULL, NULL))
        {
        	LOGE("Unable to initialize display");
        	goto ERROR;
        }

        // Selects the first OpenGL configuration found.
        LOGD("Selecting a display config.");
        if(!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1, &lNumConfigs) || (lNumConfigs <= 0))
        {
        	LOGE("Unable to select display configuration");
        	goto ERROR;
        }

        // Reconfigures the Android window with the EGL format.
        LOGD("Configuring window format.");
        if (!eglGetConfigAttrib(mDisplay, lConfig, EGL_NATIVE_VISUAL_ID, &lFormat))
        {
        	LOGE("Unable to configure window format");
        	goto ERROR;
        }
        ANativeWindow_setBuffersGeometry(Global::pAndroidApp->window, 0, 0, lFormat);
        // Creates the display surface.
        LOGD("Initializing the display.");
        mSurface = eglCreateWindowSurface(mDisplay, lConfig, Global::pAndroidApp->window, NULL);
        if (mSurface == EGL_NO_SURFACE)
        {
        	LOGE("EGL_NO_SURFACE");
        	goto ERROR;
        }
        mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, lContextAttrib);
        if (mContext == EGL_NO_CONTEXT)
        {
        	LOGE("EGL_NO_CONTEXT");
        	goto ERROR;
        }

        // Activates the display surface.
        LOGD("Activating the display.");
        if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
         || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth)
         || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight)
         || (mWidth <= 0) || (mHeight <= 0))
        {
        	LOGE("Unable to activate display");
        	goto ERROR;
        }

        // Displays information about OpenGL.
        LOGI("Starting GraphicsService");
        LOGI("Version  : %s", glGetString(GL_VERSION));
        LOGI("Vendor   : %s", glGetString(GL_VENDOR));
        LOGI("Renderer : %s", glGetString(GL_RENDERER));
        LOGI("Viewport : %d x %d", mWidth, mHeight);

		Setup(mWidth,mHeight);
		return STATUS_OK;

    ERROR:
    	LOGE("Error while starting GraphicsService");
        Stop();
        return STATUS_KO;
    }

    void GraphicsService::Stop()
    {
    	LOGI("GraphicsService::Stop");

    	UnloadResources();

    	Render::DisableOrthoMode();

        // Destroys OpenGL context.
        if (mDisplay != EGL_NO_DISPLAY)
        {
            eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (mContext != EGL_NO_CONTEXT)
            {
                eglDestroyContext(mDisplay, mContext);
                mContext = EGL_NO_CONTEXT;
            }
            if (mSurface != EGL_NO_SURFACE)
            {
                eglDestroySurface(mDisplay, mSurface);
                mSurface = EGL_NO_SURFACE;
            }
            eglTerminate(mDisplay);
            mDisplay = EGL_NO_DISPLAY;
        }
    }

    void GraphicsService::Setup(int width, int height)
    {
    	Render::Init();
		Render::SetScreenSize(width,height);
		Render::SetOrthoMode();
		Render::EnableOrthoMode();

		LoadResources();
    }

    void GraphicsService::Update()
    {
        float lTimeStep = Global::pContext->pTimeService->Elapsed();

        ParticleEmitter::UpdateAll(lTimeStep);
        Particle::UpdateAll(lTimeStep);
    }

    Status GraphicsService::Render()
    {
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	Particle::RenderAll();
		SpriteBatcher::Flush();

		if(eglSwapBuffers(mDisplay, mSurface)!=EGL_TRUE)
		{
			LOGE("Error %d swapping buffers.",eglGetError());
			return STATUS_KO;
		}

		return STATUS_OK;
    }

    Status GraphicsService::LoadResources()
    {
    	InitVertexPrograms();

    	Global::pFont=new TextureMappedFont;
    	Global::pFont->Load("@Font.tga");

    	return STATUS_OK;
    }

    Status GraphicsService::UnloadResources()
    {
    	delete Global::pFont;

    	DeleteVertexPrograms();

    	return STATUS_OK;
    }
}
