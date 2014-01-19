#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSINPUTSERVICE_HPP
#define WINDOWSINPUTSERVICE_HPP

#include "Types.hpp"
#include "Mouse.hpp"

namespace Core
{
	class WindowsInputService
	{
	public:
		WindowsInputService();
		~WindowsInputService();

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
		PBYTE		m_currKeyboard;
		PBYTE		m_lastKeyboard;
		Mouse 		m_mouseBuffer1;
		Mouse 		m_mouseBuffer2;
	};
}

#endif

#endif
