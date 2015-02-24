#ifdef LINUX_PLATFORM

#include "LinuxInputService.hpp"

#include "LinuxMouseInterface.hpp"
#include "LinuxKeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		LinuxInputService::LinuxInputService()
		{
			m_pMouse = new LinuxMouseInterface;
			m_pKeyboard = new LinuxKeyboardInterface;
			Reset();
		}

		LinuxInputService::~LinuxInputService()
		{
		}

		void LinuxInputService::Update()
		{
			m_pMouse->Update();
			m_pKeyboard->Update();
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
	}
}

#endif
