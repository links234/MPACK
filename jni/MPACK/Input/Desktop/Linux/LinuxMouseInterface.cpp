#ifdef LINUX_PLATFORM

#include "LinuxMouseInterface.hpp"

#include <stdexcept>
#include <cassert>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <algorithm>
#include "Global.hpp"
#include "LinuxEventLoop.hpp"

namespace MPACK
{
	namespace Input
	{
		LinuxMouseInterface::LinuxMouseInterface()
		{
		}

		LinuxMouseInterface::~LinuxMouseInterface()
		{
		}

		void LinuxMouseInterface::Update()
		{
			memcpy(m_pLastState,m_pCurrState,sizeof(m_stateBuffer1));

			Window *m_window=NULL;
			if(Global::pEventLoop)
			{
				m_window=(Window*)(Global::pEventLoop->GetWindowHandle());
			}

			if(m_window)
			{
				Display *dpy;
				Window root;
				Window ret_root;
				Window ret_child;
				int root_x;
				int root_y;
				int winX;
				int winY;
				unsigned int mask;

				dpy = XOpenDisplay(NULL);
				root = XDefaultRootWindow(dpy);

				if(XQueryPointer(dpy, *m_window, &ret_root, &ret_child, &root_x, &root_y,
							 &winX, &winY, &mask))
				{
					m_pCurrState->Pos.x = winX;
					m_pCurrState->Pos.y = winY;

					m_pCurrState->Button.Left = (mask & Button1Mask) ? true : false;
					m_pCurrState->Button.Middle = (mask & Button2Mask) ? true : false;
					m_pCurrState->Button.Right = (mask & Button3Mask) ? true : false;
				}

				XCloseDisplay(dpy);
			}
		}
	}
}

#endif

