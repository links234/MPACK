#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSKEYBOARDINTERFACE_HPP
#define WINDOWSKEYBOARDINTERFACE_HPP

#include "KeyboardInterface.hpp"

namespace Core
{
	class WindowsKeyboardInterface : public KeyboardInterface
	{
	public:
		WindowsKeyboardInterface();
		~WindowsKeyboardInterface();

		void Update();

		KeyCode TranslateCode(const int &code);
	};
}

#endif

#endif
