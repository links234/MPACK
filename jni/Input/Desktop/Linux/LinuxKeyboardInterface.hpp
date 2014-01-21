#ifdef LINUX_PLATFORM

#ifndef LINUXKEYBOARDINTERFACE_HPP
#define LINUXKEYBOARDINTERFACE_HPP

#include "KeyboardInterface.hpp"

namespace Core
{
	class LinuxKeyboardInterface : public KeyboardInterface
	{
	public:
		LinuxKeyboardInterface();
		~LinuxKeyboardInterface();

		void Update();

		KeyCode TranslateCode(const int &code);
	};
}

#endif

#endif
