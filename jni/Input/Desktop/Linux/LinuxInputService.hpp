#ifdef LINUX_PLATFORM

#ifndef LINUXINPUTSERVICE_HPP
#define LINUXINPUTSERVICE_HPP

#include "Types.hpp"
#include "Mouse.hpp"

namespace Core
{
	class LinuxInputService
	{
	public:
		LinuxInputService();
		~LinuxInputService();

		void Update();
		void Reset();

		bool KeyDown(int key);
		bool KeyUp(int key);
		bool KeyPressed(int key);

		Mouse 		*m_currMouse;
		Mouse 		*m_lastMouse;
	private:
		BYTE		m_keyboardBuffer1[256];
		BYTE		m_keyboardBuffer2[256];
		BYTE		*m_currKeyboard;
		BYTE		*m_lastKeyboard;
		Mouse 		m_mouseBuffer1;
		Mouse 		m_mouseBuffer2;
	};
}

#endif

#endif
