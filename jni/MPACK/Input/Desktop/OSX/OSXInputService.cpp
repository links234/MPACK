#ifdef OSX_PLATFORM

#include "OSXInputService.hpp"

#include "InputService.hpp"
#include "OSXMouseInterface.hpp"
#include "OSXKeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		OSXInputService::OSXInputService()
		{
			LOGI("Creating InputService.");
			m_pFinger = new Finger;
			m_pMouse = new OSXMouseInterface;
			m_pKeyboard = new OSXKeyboardInterface;
			Reset();
		}

		OSXInputService::~OSXInputService()
		{
			LOGI("Destroying InputService.");
			delete m_pFinger;
			delete m_pMouse;
			delete m_pKeyboard;
		}

		void OSXInputService::Update()
		{
			m_pMouse->Update();
			m_pKeyboard->Update();

			EmulateTouchscreenFinger();
		}

		void OSXInputService::Reset()
		{
			m_pMouse->Reset();
			m_pKeyboard->Reset();
		}

		MouseInterface* OSXInputService::GetMouse() const
		{
			return m_pMouse;
		}

		KeyboardInterface* OSXInputService::GetKeyboard() const
		{
			return m_pKeyboard;
		}

		void OSXInputService::EmulateTouchscreenFinger()
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

		void OSXInputService::ClearLinks()
		{
			m_callbackFunc_FDOWN.clear();
			m_callbackFunc_FUP.clear();
			m_callbackFunc_KEYBACK.clear();
		}

		void OSXInputService::Link_FUP(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FUP.push_back(link);
		}

		void OSXInputService::Link_FDOWN(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FDOWN.push_back(link);
		}

		void OSXInputService::Link_KEYBACK(const Param1PtrCallbackStruct &link)
		{
			m_callbackFunc_KEYBACK.push_back(link);
		}

		void OSXInputService::UnLink_FUP(const Param2PtrCallbackStruct &link)
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

		void OSXInputService::UnLink_FDOWN(const Param2PtrCallbackStruct &link)
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

		void OSXInputService::UnLink_KEYBACK(const Param1PtrCallbackStruct &link)
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
