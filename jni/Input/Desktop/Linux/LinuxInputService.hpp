#ifdef LINUX_PLATFORM

#ifndef LINUXINPUTSERVICE_HPP
#define LINUXINPUTSERVICE_HPP

#include "Types.hpp"
#include "MouseInterface.hpp"
#include "KeyboardInterface.hpp"

namespace Core
{
	class LinuxInputService
	{
	public:
		LinuxInputService();
		~LinuxInputService();

		void Update();
		void Reset();

		KeyboardInterface*	GetKeyboard() const;

		MouseInterface 		*m_currMouse;
		MouseInterface 		*m_lastMouse;
	private:
		MouseInterface 		m_mouseBuffer1;
		MouseInterface 		m_mouseBuffer2;

		KeyboardInterface	*m_pKeyboard;
	};
}

#endif

#endif
