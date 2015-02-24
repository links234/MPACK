#ifdef WINDOWS_PLATFORM

#include "WindowsMouseInterface.hpp"

#include "WindowsEventLoop.hpp"

#include "Global.hpp"

namespace MPACK
{
	namespace Input
	{
		WindowsMouseInterface::WindowsMouseInterface()
		{
		}

		WindowsMouseInterface::~WindowsMouseInterface()
		{
		}

		void WindowsMouseInterface::Update()
		{
			memcpy(m_pLastState,m_pCurrState,sizeof(m_stateBuffer1));

			POINT p;
			GetCursorPos(&p);

			if(Global::pEventLoop)
			{
				ScreenToClient(*((HWND*)(Global::pEventLoop->GetWindowHandle())),&p);
			}

			m_pCurrState->Pos.x=(float)p.x;
			m_pCurrState->Pos.y=(float)p.y;
			m_pCurrState->Button.Left=m_pCurrState->Button.Middle=m_pCurrState->Button.Right=false;
			if(GetKeyState(VK_LBUTTON) & 0x80)
			{
				m_pCurrState->Button.Left=true;
			}
			if(GetKeyState(VK_MBUTTON) & 0x80)
			{
				m_pCurrState->Button.Middle=true;
			}
			if(GetKeyState(VK_RBUTTON) & 0x80)
			{
				m_pCurrState->Button.Right=true;
			}
			m_pCurrState->Wheel=m_pLastState->Wheel;
		}
	}
}

#endif

