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
			EGLWindow();
			~EGLWindow();

			ReturnValue Init();
			ReturnValue ChooseConfig(EGLint redSize=8, EGLint greenSize=8, EGLint blueSize=8, EGLint depthSize=24);
			ReturnValue GetFormat(EGLint &format) const;
			ReturnValue CreateSurface(NativeWindowType &window);
			ReturnValue CreateContext();
			ReturnValue Bind(EGLint &width, EGLint &height);
			void Destroy();

			bool IsContextBound();
			bool IsSurfaceCreated();
			bool IsContextCreated();

			void InvalidateSurface();
			void InvalidateContext();

			ReturnValue SwapBuffers();

			EGLint GetMajorVersion() const;
			EGLint GetMinorVersion() const;

		private:
			EGLDisplay 	m_display;
			EGLSurface	m_surface;
			EGLContext 	m_context;

			EGLConfig 	m_config;

			EGLint 		m_majorVersion, m_minorVersion;

			bool 		m_isContextBound;
			bool		m_haveSurface;
			bool		m_haveContext;

			friend class EGLBufferConfigManager;
		};
	}
}

#endif

#endif
