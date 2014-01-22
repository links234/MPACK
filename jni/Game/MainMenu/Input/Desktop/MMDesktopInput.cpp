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
		m_pFinger->m_pos=Global::pContext->pInputService->GetMouse()->GetPosition();
	}

	if(Global::pContext->pInputService->GetMouse()->ButtonDown(MBC_LEFT))
	{
			m_pFinger=new Finger();
			m_pFinger->m_flag=Finger::FREE;
			m_pFinger->m_pos=Global::pContext->pInputService->GetMouse()->GetPosition();

			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FDOWN.begin();it!=m_callbackFunc_FDOWN.end();++it)
			{
				it->function(it->param1,m_pFinger);
			}
	}
	else if(Global::pContext->pInputService->GetMouse()->ButtonUp(MBC_LEFT))
	{
		for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FUP.begin();it!=m_callbackFunc_FUP.end();++it)
		{
			it->function(it->param1,m_pFinger);
		}

		delete m_pFinger;
		m_pFinger=NULL;
	}
}

#endif
