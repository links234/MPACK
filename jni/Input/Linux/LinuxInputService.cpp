#ifdef LINUX_PLATFORM

#include "LinuxInputService.hpp"

#include <algorithm>
#include "Global.hpp"

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
