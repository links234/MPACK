#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSINPUTSERVICE_HPP
#define WINDOWSINPUTSERVICE_HPP

#include "Types.hpp"
#include "MouseInterface.hpp"
#include "KeyboardInterface.hpp"

namespace Core
{
	class WindowsInputService
	{
	public:
		WindowsInputService();
		~WindowsInputService();

		void Update();
		void Reset();

		MouseInterface*		GetMouse() const;
		KeyboardInterface* 	GetKeyboard() const;

	private:

		MouseInterface		*m_pMouse;
		KeyboardInterface	*m_pKeyboard;
	};
}

#endif

#endif
