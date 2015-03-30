#ifndef MPACK_EGLWINDOW_HPP
#define MPACK_EGLWINDOW_HPP

#include "Types.hpp"

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
			ReturnValue ChooseConfig();
			ReturnValue GetFormat(EGLint &format) const;
			ReturnValue CreateSurface(NativeWindowType &window);
			ReturnValue Bind(EGLint &width, EGLint &height);
			void Destroy();

			ReturnValue SwapBuffers();

			EGLint GetMajorVersion() const;
			EGLint GetMinorVersion() const;

		private:
			EGLDisplay 	m_display;
			EGLSurface	m_surface;
			EGLContext 	m_context;

			EGLConfig 	m_config;

			EGLint 		m_majorVersion, m_minorVersion;
		};
	}
}

#endif
