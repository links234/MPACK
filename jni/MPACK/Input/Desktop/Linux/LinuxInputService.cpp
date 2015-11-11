#ifdef LINUX_PLATFORM

#include "LinuxInputService.hpp"

#include "InputService.hpp"
#include "LinuxMouseInterface.hpp"
#include "LinuxKeyboardInterface.hpp"

using namespace std;
using namespace MPACK;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Input
	{
		LinuxInputService::LinuxInputService()
		{
			LOGI("Creating InputService.");
			m_pFinger = new Finger;
			m_pMouse = new LinuxMouseInterface;
			m_pKeyboard = new LinuxKeyboardInterface;
			Reset();
		}

		LinuxInputService::~LinuxInputService()
		{
			LOGI("Destroying InputService.");
			delete m_pFinger;
			delete m_pMouse;
			delete m_pKeyboard;
		}

		void LinuxInputService::Update()
		{
			m_pMouse->Update();
			m_pKeyboard->Update();

			EmulateTouchscreenFinger();
		}

		void LinuxInputService::Reset()
		{
			m_pMouse->Reset();
			m_pKeyboard->Reset();
		}

		MouseInterface* LinuxInputService::GetMouse() const
		{
			return m_pMouse;
		}

		KeyboardInterface* LinuxInputService::GetKeyboard() const
		{
			return m_pKeyboard;
		}

		void LinuxInputService::EmulateTouchscreenFinger()
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

		void LinuxInputService::ClearLinks()
		{
			m_callbackFunc_FDOWN.clear();
			m_callbackFunc_FUP.clear();
			m_callbackFunc_KEYBACK.clear();
		}

		void LinuxInputService::Link_FUP(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FUP.push_back(link);
		}

		void LinuxInputService::Link_FDOWN(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FDOWN.push_back(link);
		}

		void LinuxInputService::Link_KEYBACK(const Param1PtrCallbackStruct &link)
		{
			m_callbackFunc_KEYBACK.push_back(link);
		}

		void LinuxInputService::UnLink_FUP(const Param2PtrCallbackStruct &link)
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

		void LinuxInputService::UnLink_FDOWN(const Param2PtrCallbackStruct &link)
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

		void LinuxInputService::UnLink_KEYBACK(const Param1PtrCallbackStruct &link)
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
