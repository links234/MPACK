#ifdef ANDROID_PLATFORM

#ifndef MPACK_EGLWINDOW_HPP
#define MPACK_EGLWINDOW_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		class EGLBufferConfigManager;
	}
}

namespace MPACK
{
	namespace Core
	{
		class EGLWindow
		{
		public:
			enum
			{
				EGL_UNINITIALIZED = 0,
				EGL_INITIALIZED = 1,
				EGL_HAS_SURFACE = 2,
				EGL_IS_BOUND = 3
			};

			EGLWindow();
			~EGLWindow();

			ReturnValue Init();
			ReturnValue ChooseConfig(EGLint redSize=8, EGLint greenSize=8, EGLint blueSize=8, EGLint depthSize=24);

			bool Bind();
			bool Unbind();

			void Destroy();

			bool SetWindow(ANativeWindow* window);

			ReturnValue SwapBuffers();

			EGLint GetMajorVersion() const;
			EGLint GetMinorVersion() const;

			int32_t GetSurfaceWidth();
			int32_t GetSurfaceHeight();

			bool CreateContext();

			bool CreateSurface();
			bool DestroySurface();

			bool IsReadyToRender(bool allocateIfNeeded);

			bool IsBound();
			bool HasSurface();
			bool HasContext();

			EGLDisplay GetDisplay();
			EGLConfig GetConfig();
			EGLContext GetContext();
			EGLSurface GetSurface();
			ANativeWindow* GetWindow();

		private:
			EGLDisplay 		m_display;
			EGLSurface		m_surface;
			EGLContext 		m_context;
			ANativeWindow* 	m_window;
			int 			m_status;
			int 			m_width;
			int				m_height;

			EGLConfig 		m_config;

			EGLint 		m_majorVersion, m_minorVersion;

			friend class EGLBufferConfigManager;
		};
	}
}

#endif

#endif
