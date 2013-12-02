#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "MMDesktopInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"

MMDesktopInput::MMDesktopInput()
	: m_pFinger(NULL)
{
}

MMDesktopInput::~MMDesktopInput()
{
}

void MMDesktopInput::Update(GLfloat delta)
{
	if(m_pFinger)
	{
		m_pFinger->m_pos=Global::pContext->pInputService->m_currMouse->Pos;
	}

	if(Global::pContext->pInputService->m_currMouse->Button.Left!=Global::pContext->pInputService->m_lastMouse->Button.Left)
	{
		if(Global::pContext->pInputService->m_currMouse->Button.Left)
		{
			m_pFinger=new Finger();
			m_pFinger->m_flag=Finger::FREE;
			m_pFinger->m_pos=Global::pContext->pInputService->m_currMouse->Pos;

			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FDOWN.begin();it!=m_callbackFunc_FDOWN.end();++it)
			{
				it->function(it->param1,m_pFinger);
			}
		}
		else
		{
			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FUP.begin();it!=m_callbackFunc_FUP.end();++it)
			{
				it->function(it->param1,m_pFinger);
			}

			delete m_pFinger;
			m_pFinger=NULL;
		}
	}
}

#endif
