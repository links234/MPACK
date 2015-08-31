#ifdef ANDROID_PLATFORM

#include "EGLWindow.hpp"

namespace MPACK
{
	namespace Core
	{
		EGLWindow::EGLWindow()
			: m_display(EGL_NO_DISPLAY), m_surface(EGL_NO_CONTEXT), m_context(EGL_NO_SURFACE),
			  m_config(0), m_majorVersion(0), m_minorVersion(0),
			  m_isContextBound(false), m_haveSurface(false), m_haveContext(false)
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
			return RETURN_VALUE_OK;
		}

		ReturnValue EGLWindow::GetFormat(EGLint &format) const
		{
			EGLint result = 0;
			EGL_CHECK( result = eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &format) );
			if (!result)
			{
				LOGE("EGLDisplay::GetFormat() unable to configure window format");
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue EGLWindow::CreateSurface(NativeWindowType &window)
		{
			EGL_CHECK( m_surface = eglCreateWindowSurface(m_display, m_config, window, NULL) );
			if (m_surface == EGL_NO_SURFACE)
			{
				LOGE("EGLDisplay::CreateSurface() failed to create surface");
				return RETURN_VALUE_KO;
			}
			m_haveSurface = true;
			return RETURN_VALUE_OK;
		}

		ReturnValue EGLWindow::CreateContext()
		{
			const EGLint contextAttrib[] =
			{
				EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
			};

			EGL_CHECK( m_context = eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, contextAttrib) );
			if (m_context == EGL_NO_CONTEXT)
			{
				LOGE("EGLDisplay::CreateContext() failed to create context");
				return RETURN_VALUE_KO;
			}

			m_haveContext = true;
			return RETURN_VALUE_OK;
		}

		ReturnValue EGLWindow::Bind(EGLint &width, EGLint &height)
		{
			EGLint result = 0;

			width=0;
			height=0;

			EGL_CHECK( result = eglMakeCurrent(m_display, m_surface, m_surface, m_context) );
			if(!result)
			{
				LOGE("EGLDisplay::Bind() failed to bind display");
				return RETURN_VALUE_KO;
			}

			EGL_CHECK( result = eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width) );
			if(!result)
			{
				LOGE("EGLDisplay::Bind() failed to get display width");
				return RETURN_VALUE_KO;
			}

			EGL_CHECK( result = eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height) );
			if(!result)
			{
				LOGE("EGLDisplay::Bind() failed to get display height");
				return RETURN_VALUE_KO;
			}

			m_isContextBound = true;
			return RETURN_VALUE_OK;
		}

		void EGLWindow::Destroy()
		{
			m_isContextBound = false;
			m_haveSurface = false;
			m_haveContext = false;

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
		}

		bool EGLWindow::IsContextBound()
		{
			return m_isContextBound;
		}

		bool EGLWindow::IsSurfaceCreated()
		{
			return m_haveSurface;
		}

		bool EGLWindow::IsContextCreated()
		{
			return m_haveContext;
		}

		void EGLWindow::InvalidateSurface()
		{
			LOGD("SURFACE INVALIDATED");
			m_isContextBound = false;
			m_haveSurface = false;
		}

		void EGLWindow::InvalidateContext()
		{
			m_haveContext=false;
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
	}
}

#endif
