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

		MouseInterface*		GetMouse()		const;
		KeyboardInterface*	GetKeyboard() 	const;

	private:
		MouseInterface		*m_pMouse;
		KeyboardInterface	*m_pKeyboard;
	};
}

#endif

#endif
