#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXEVENTLOOP_HPP
#define MPACK_LINUXEVENTLOOP_HPP

#include "Types.hpp"
#include "EventLoop.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include <ctime>
#include <string>
#include <iostream>

namespace MPACK
{
	namespace Core
	{
		class Application;
	}
}

namespace MPACK
{
	namespace Core
	{
		class LinuxEventLoop : public EventLoop
		{
		public:
			LinuxEventLoop(void *data);
			ReturnValue Run(Application* pApplication);

			void ShowCursor();
			void HideCursor();

			void* GetWindowHandle() const;

		protected:

			Status InitializeDisplay();
			void DestroyDisplay();

			void SetupPixelFormat();

			void ProcessEvents();
			void SwapBuffers();

			Display* m_display;
			Window m_XWindow;
			GLXContext m_glContext;
			XF86VidModeModeInfo m_XF86DeskMode;
			XSetWindowAttributes m_XSetAttr;
			int m_screenID;

			unsigned int m_width;
			unsigned int m_height;
			unsigned int m_bpp;

			unsigned int m_newWidth;
			unsigned int m_newHeight;

			bool	m_isResizing;
			bool	m_isRunning;
			bool	m_isFullscreen;
			bool	m_enabled;
			bool 	m_GL3Supported;
		};
	}
}

#endif

#endif
