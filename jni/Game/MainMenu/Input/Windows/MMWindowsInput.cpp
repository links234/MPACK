#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#include "MMWindowsInput.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "InputService.hpp"

MMWindowsInput::MMWindowsInput()
	: m_pFinger(NULL)
{
}

MMWindowsInput::~MMWindowsInput()
{
}

void MMWindowsInput::Update(GLfloat delta)
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
