#ifdef ANDROID_PLATFORM

#include "EGLWindow.hpp"

namespace MPACK
{
	namespace Core
	{
		EGLWindow::EGLWindow()
			: m_display(EGL_NO_DISPLAY), m_surface(EGL_NO_CONTEXT), m_context(EGL_NO_SURFACE),
			  m_window(NULL), m_status(EGL_UNINITIALIZED),
			  m_config(0), m_majorVersion(0), m_minorVersion(0),
			  m_width(0), m_height(0)
		{
		}

		EGLWindow::~EGLWindow()
		{
			Destroy();
		}

		ReturnValue EGLWindow::Init()
		{
			EGL_CHECK( m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY) );
			if (m_display == EGL_NO_DISPLAY)
			{
				LOGE("EGLDisplay::Init() failed to get default display");
				return RETURN_VALUE_KO;
			}
			EGLint result = 0;
			EGL_CHECK( result = eglInitialize(m_display, &m_majorVersion, &m_minorVersion) );
			LOGI("EGL version: %d.%d", m_majorVersion, m_minorVersion);
			if (!result)
			{
				LOGE("EGLDisplay::Init() unable to initialize display");
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue EGLWindow::ChooseConfig(EGLint redSize, EGLint greenSize, EGLint blueSize, EGLint depthSize)
		{
			EGLint numConfigs = 0;
			EGLint result = 0;

			const EGLint attributes[] =
			{
				EGL_RENDERABLE_TYPE, EGL_WINDOW_BIT,
				EGL_RED_SIZE, redSize,
				EGL_GREEN_SIZE, greenSize,
				EGL_BLUE_SIZE, blueSize,
				EGL_DEPTH_SIZE, depthSize,
				EGL_NONE
			};

			EGL_CHECK( result = eglChooseConfig(m_display, attributes, &m_config, 1, &numConfigs) );
			if(!result || (numConfigs <= 0))
			{
				LOGE("EGLDisplay::ChooseConfig() unable to select display configuration");
				return RETURN_VALUE_KO;
			}

			m_status = EGL_INITIALIZED;

			return RETURN_VALUE_OK;
		}

		bool EGLWindow::CreateContext()
		{
			const EGLint contextAttrib[] =
			{
				EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
			};

			EGL_CHECK( m_context = eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, contextAttrib) );
			if (m_context == EGL_NO_CONTEXT)
			{
				LOGE("EGLDisplay::CreateContext() failed to create context");
				return false;
			}

			return true;
		}

		void EGLWindow::Destroy()
		{
			m_majorVersion = 0;
			m_minorVersion = 0;
			if (m_display != EGL_NO_DISPLAY)
			{
				EGL_CHECK( eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) );
				if (m_context != EGL_NO_CONTEXT)
				{
					EGL_CHECK( eglDestroyContext(m_display, m_context) );
					m_context = EGL_NO_CONTEXT;
				}
				if (m_surface != EGL_NO_SURFACE)
				{
					EGL_CHECK( eglDestroySurface(m_display, m_surface) );
					m_surface = EGL_NO_SURFACE;
				}
				EGL_CHECK( eglTerminate(m_display) );
				m_display = EGL_NO_DISPLAY;
			}
			m_status = EGL_UNINITIALIZED;
		}

		bool EGLWindow::SetWindow(ANativeWindow* window)
		{
		    if (window != m_window)
		    {
		        LOGI("EGLWindow::SetWindow() Window has changed!");
		        DestroySurface();
		    }

		    m_window = window;

		    m_width = m_window ? ANativeWindow_getWidth(m_window) : 0;
		    m_height = m_window ? ANativeWindow_getHeight(m_window) : 0;

		    return true;
		}

		bool EGLWindow::CreateSurface()
		{
		    if (m_status >= EGL_HAS_SURFACE)
		        return true;

		    if (!m_window)
		        return false;

		    if (m_status < EGL_INITIALIZED)
		        return false;

		    EGLint m_format;
		    EGLint result = 0;
			EGL_CHECK( result = eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &m_format) );
			if (!result)
			{
				LOGE("EGLDisplay::CreateSurface() unable to configure window format");
				return false;
			}

		    ANativeWindow_setBuffersGeometry(m_window, 0, 0, m_format);

		    EGL_CHECK( m_surface = eglCreateWindowSurface(m_display, m_config, m_window, NULL) );
		    if (m_surface != EGL_NO_SURFACE)
		    {
		        int32_t w = ANativeWindow_getWidth(m_window);
		        int32_t h = ANativeWindow_getHeight(m_window);
		        EGLint sw, sh;
		        eglQuerySurface(m_display, m_surface, EGL_WIDTH, &sw);
		        eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &sh);
		        //mNewWindow = true;
		    }
		    else
		    {
		        return false;
		    }

		    m_status = EGL_HAS_SURFACE;

		    return true;
		}

		bool EGLWindow::IsReadyToRender(bool allocateIfNeeded)
		{
		    if (m_status >= EGL_IS_BOUND)
		    {
		        return true;
		    }

		    if (!allocateIfNeeded)
		    {
		        return false;
		    }

		    // If we have not bound the context and surface, do we even _have_ a surface?
		    if (m_status < EGL_HAS_SURFACE)
		    {
		        if (m_status < EGL_INITIALIZED)
		        {
		            return false;
		        }
		        if (!CreateSurface())
		        {
		            return false;
		        }
		    }

		    // We have a surface and (possibly) context, so bind them
		    if (!Bind())
		    {
		        return false;
		    }

		    return true;
		}

		bool EGLWindow::Bind()
		{
		    if (m_status >= EGL_IS_BOUND)
		        return true;

		    if (m_status < EGL_HAS_SURFACE)
		        return false;

		    if (m_context == EGL_NO_CONTEXT)
		    {
		        LOGI("EGLWindow::Bind() Creating context inside of bind()");
		        if (!CreateContext())
		            return false;
		    }

		    EGL_CHECK( eglMakeCurrent(m_display, m_surface, m_surface, m_context) );

		    m_status = EGL_IS_BOUND;

		    return true;
		}

		bool EGLWindow::Unbind()
		{
		    if (m_status < EGL_IS_BOUND)
		        return true;

		    EGL_CHECK( eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) );

		    m_status = EGL_HAS_SURFACE;

		    return true;
		}

		int32_t EGLWindow::GetSurfaceWidth()
		{
		    EGLint width;
		    if ((m_status >= EGL_HAS_SURFACE) && eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width))
		    {
		        return width;
		    }
		    else
		    {
		    	return m_width;
		    }
		}

		int32_t EGLWindow::GetSurfaceHeight()
		{
		    EGLint height;
		    if ((m_status >= EGL_HAS_SURFACE) && eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height))
		    {
		        return height;
		    }
		    else
		    {
		    	return m_height;
		    }
		}

		bool EGLWindow::DestroySurface()
		{
		    if (m_status < EGL_HAS_SURFACE)
		        return true;

		    if (m_status >= EGL_IS_BOUND)
		    {
		        EGL_CHECK( eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) );
		    }

		    EGL_CHECK( eglDestroySurface(m_display, m_surface) );

		    m_surface = EGL_NO_SURFACE;

		    m_status = EGL_INITIALIZED;

		    return true;
		}

		ReturnValue EGLWindow::SwapBuffers()
		{
			EGLint result = 0;
			EGL_CHECK( result = eglSwapBuffers(m_display, m_surface) );
			if(result != EGL_TRUE)
			{
				LOGE("EGLWindow::SwapBuffers() error");
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		EGLint EGLWindow::GetMajorVersion() const
		{
			return m_majorVersion;
		}

		EGLint EGLWindow::GetMinorVersion() const
		{
			return m_minorVersion;
		}

		bool EGLWindow::IsBound()
		{
			return m_status == EGL_IS_BOUND;
		}

		bool EGLWindow::HasSurface()
		{
			return m_status >= EGL_HAS_SURFACE;
		}

		bool EGLWindow::HasContext()
		{
			return m_context != EGL_NO_CONTEXT;
		}

		EGLDisplay EGLWindow::GetDisplay()
		{
			return m_display;
		}

		EGLConfig EGLWindow::GetConfig()
		{
			return m_config;
		}

		EGLContext EGLWindow::GetContext()
		{
			return m_context;
		}

		EGLSurface EGLWindow::GetSurface()
		{
			return m_surface;
		}

		ANativeWindow* EGLWindow::GetWindow()
		{
			return m_window;
		}
	}
}

#endif
