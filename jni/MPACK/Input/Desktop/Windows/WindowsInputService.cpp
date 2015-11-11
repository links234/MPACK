#ifdef WINDOWS_PLATFORM

#include "WindowsInputService.hpp"

#include "WindowsMouseInterface.hpp"
#include "WindowsKeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		WindowsInputService::WindowsInputService()
		{
			LOGI("Creating InputService.");
			m_pFinger = new Finger;
			m_pMouse = new WindowsMouseInterface;
			m_pKeyboard = new WindowsKeyboardInterface;
			Reset();
		}

		WindowsInputService::~WindowsInputService()
		{
			LOGI("Destroying InputService.");
			delete m_pFinger;
			delete m_pMouse;
			delete m_pKeyboard;
		}

		void WindowsInputService::Update()
		{
			m_pMouse->Update();
			m_pKeyboard->Update();

			EmulateTouchscreenFinger();
		}

		void WindowsInputService::Reset()
		{
			m_pMouse->Reset();
			m_pKeyboard->Reset();
		}

		MouseInterface* WindowsInputService::GetMouse() const
		{
			return m_pMouse;
		}

		KeyboardInterface* WindowsInputService::GetKeyboard() const
		{
			return m_pKeyboard;
		}

		void WindowsInputService::EmulateTouchscreenFinger()
		{
			if(m_pMouse->ButtonPressed(MBC_LEFT))
			{
				m_pFinger->m_pos = m_pMouse->GetPosition();
			}

			if(m_pMouse->ButtonDown(MBC_LEFT))
			{
				m_pFinger->m_flag = Finger::FREE;
				m_pFinger->m_pos = m_pMouse->GetPosition();
				for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FDOWN.begin();it!=m_callbackFunc_FDOWN.end();++it)
				{
					it->function(it->param1,(void*)(m_pFinger));
				}
			}
			else if(m_pMouse->ButtonUp(MBC_LEFT))
			{
				for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FUP.begin();it!=m_callbackFunc_FUP.end();++it)
				{
					it->function(it->param1,(void*)(m_pFinger));
				}
			}

			if(m_pKeyboard->KeyPressed(KC_ESCAPE))
			{
				for(vector<Param1PtrCallbackStruct>::iterator it=m_callbackFunc_KEYBACK.begin();it!=m_callbackFunc_KEYBACK.end();++it)
				{
					(*it).function((*it).param1);
				}
			}
		}

		void WindowsInputService::ClearLinks()
		{
			m_callbackFunc_FDOWN.clear();
			m_callbackFunc_FUP.clear();
			m_callbackFunc_KEYBACK.clear();
		}

		void WindowsInputService::Link_FUP(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FUP.push_back(link);
		}

		void WindowsInputService::Link_FDOWN(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FDOWN.push_back(link);
		}

		void WindowsInputService::Link_KEYBACK(const Param1PtrCallbackStruct &link)
		{
			m_callbackFunc_KEYBACK.push_back(link);
		}

		void WindowsInputService::UnLink_FUP(const Param2PtrCallbackStruct &link)
		{
			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FUP.begin();it!=m_callbackFunc_FUP.end();++it)
			{
				if(*it==link)
				{
					m_callbackFunc_FUP.erase(it);
					return;
				}
			}
		}

		void WindowsInputService::UnLink_FDOWN(const Param2PtrCallbackStruct &link)
		{
			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FDOWN.begin();it!=m_callbackFunc_FDOWN.end();++it)
			{
				if(*it==link)
				{
					m_callbackFunc_FDOWN.erase(it);
					return;
				}
			}
		}

		void WindowsInputService::UnLink_KEYBACK(const Param1PtrCallbackStruct &link)
		{
			for(vector<Param1PtrCallbackStruct>::iterator it=m_callbackFunc_KEYBACK.begin();it!=m_callbackFunc_KEYBACK.end();++it)
			{
				if(*it==link)
				{
					m_callbackFunc_KEYBACK.erase(it);
					return;
				}
			}
		}
	}
}

#endif
