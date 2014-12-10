#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXINPUTSERVICE_HPP
#define MPACK_LINUXINPUTSERVICE_HPP

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
