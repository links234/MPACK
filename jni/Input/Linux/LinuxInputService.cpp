#ifdef LINUX_PLATFORM

#include "LinuxInputService.hpp"

#include <stdexcept>
#include <cassert>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <algorithm>
#include "Global.hpp"
#include "LinuxEventLoop.hpp"

using namespace std;
using namespace Math;

namespace Core
{
	LinuxInputService::LinuxInputService()
		: m_currKeyboard(m_keyboardBuffer1), m_lastKeyboard(m_keyboardBuffer2), m_currMouse(&m_mouseBuffer1), m_lastMouse(&m_mouseBuffer2)
	{
		Reset();
	}

	LinuxInputService::~LinuxInputService()
	{
	}

	void LinuxInputService::Update()
	{
		std::swap(m_currMouse,m_lastMouse);


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
				m_currMouse->Pos.x = winX;
				m_currMouse->Pos.y = winY;

				m_currMouse->Button.Left = (mask & Button1Mask) ? true : false;
				m_currMouse->Button.Right = (mask & Button2Mask) ? true : false;
			}

			XCloseDisplay(dpy);
		}
	}

	void LinuxInputService::Reset()
	{
		m_currMouse->Wheel=0;
		m_currMouse->Pos=Vector2f(0.0f);
		m_currMouse->Button.Left=false;
		m_currMouse->Button.Right=false;
		m_currMouse->Button.Middle=false;
		m_lastMouse->Wheel=0;
		m_lastMouse->Pos=Vector2f(0.0f);
		m_lastMouse->Button.Left=false;
		m_lastMouse->Button.Right=false;
		m_lastMouse->Button.Middle=false;
		Update();
		Update();
	}

	bool LinuxInputService::KeyDown(int key)
	{
		return (m_currKeyboard[key]&0xF0) && !(m_lastKeyboard[key]&0xF0);
	}

	bool LinuxInputService::KeyUp(int key)
	{
		return !(m_currKeyboard[key]&0xF0) && (m_lastKeyboard[key]&0xF0);
	}

	bool LinuxInputService::KeyPressed(int key)
	{
		return (m_currKeyboard[key]&0xF0)!=0;
	}
}

#endif
