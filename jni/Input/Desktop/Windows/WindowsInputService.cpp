#ifdef WINDOWS_PLATFORM

#include "WindowsInputService.hpp"

#include <algorithm>
#include "Global.hpp"
#include "WindowsEventLoop.hpp"
#include "WindowsKeyboardInterface.hpp"

using namespace std;
using namespace Math;

namespace Core
{
	WindowsInputService::WindowsInputService()
		: m_currMouse(&m_mouseBuffer1), m_lastMouse(&m_mouseBuffer2)
	{
		m_pKeyboard = new WindowsKeyboardInterface;
		Reset();
	}

	WindowsInputService::~WindowsInputService()
	{
	}

	void WindowsInputService::Update()
	{
		m_pKeyboard->Update();

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
		m_pKeyboard->Reset();
	}

	KeyboardInterface* WindowsInputService::GetKeyboard() const
	{
		return m_pKeyboard;
	}
}

#endif
