#ifdef WINDOWS_PLATFORM

#include "WindowsInputService.hpp"

#include <algorithm>
#include "Global.hpp"
#include "WindowsEventLoop.hpp"

using namespace std;
using namespace Math;

namespace Core
{
	bool Mouse::Buttons::operator!= (const Mouse::Buttons &other)
	{
		if(Left!=other.Left)
		{
			return true;
		}
		if(Middle!=other.Middle)
		{
			return true;
		}
		if(Right!=other.Right)
		{
			return true;
		}
		return false;
	}

	bool Mouse::Buttons::operator== (const Mouse::Buttons &other)
	{
		if(Left!=other.Left)
		{
			return false;
		}
		if(Middle!=other.Middle)
		{
			return false;
		}
		if(Right!=other.Right)
		{
			return false;
		}
		return true;
	}


	bool Mouse::operator!= (const Mouse &other)
	{
		if(Pos!=other.Pos)
		{
			return true;
		}
		if(Wheel!=other.Wheel)
		{
			return true;
		}
		if(Button!=other.Button)
		{
			return true;
		}
		return false;
	}

	bool Mouse::operator== (const Mouse &other)
	{
		if(Pos!=other.Pos)
		{
			return false;
		}
		if(Wheel!=other.Wheel)
		{
			return false;
		}
		if(Button!=other.Button)
		{
			return false;
		}
		return true;
	}

	WindowsInputService::WindowsInputService()
		: m_currKeyboard(m_keyboardBuffer1), m_lastKeyboard(m_keyboardBuffer2), m_currMouse(&m_mouseBuffer1), m_lastMouse(&m_mouseBuffer2)
	{
		Reset();
	}

	WindowsInputService::~WindowsInputService()
	{
	}

	void WindowsInputService::Update()
	{
		std::swap(m_currKeyboard,m_lastKeyboard);
		GetKeyboardState(m_currKeyboard);
		std::swap(m_currMouse,m_lastMouse);
		POINT p;
		GetCursorPos(&p);

		if(Global::pEventLoop)
		{
			ScreenToClient(*((HWND*)(Global::pEventLoop->GetWindowHandle())),&p);
		}

		m_currMouse->Pos.x=(float)p.x;
		m_currMouse->Pos.y=(float)p.y;
		m_currMouse->Button.Left=m_currMouse->Button.Middle=m_currMouse->Button.Right=false;
		if(GetKeyState(VK_LBUTTON) & 0x80)
		{
			m_currMouse->Button.Left=true;
		}
		if(GetKeyState(VK_MBUTTON) & 0x80)
		{
			m_currMouse->Button.Middle=true;
		}
		if(GetKeyState(VK_RBUTTON) & 0x80)
		{
			m_currMouse->Button.Right=true;
		}
		m_currMouse->Wheel=m_lastMouse->Wheel;
	}

	void WindowsInputService::Reset()
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

	bool WindowsInputService::KeyDown(int key)
	{
		return (m_currKeyboard[key]&0xF0) && !(m_lastKeyboard[key]&0xF0);
	}

	bool WindowsInputService::KeyUp(int key)
	{
		return !(m_currKeyboard[key]&0xF0) && (m_lastKeyboard[key]&0xF0);
	}

	bool WindowsInputService::KeyPressed(int key)
	{
		return (m_currKeyboard[key]&0xF0)!=0;
	}
}

#endif
