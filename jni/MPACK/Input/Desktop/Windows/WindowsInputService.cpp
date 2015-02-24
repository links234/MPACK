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
			m_pMouse = new WindowsMouseInterface;
			m_pKeyboard = new WindowsKeyboardInterface;
			Reset();
		}

		WindowsInputService::~WindowsInputService()
		{
		}

		void WindowsInputService::Update()
		{
			m_pMouse->Update();
			m_pKeyboard->Update();
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
	}
}

#endif
