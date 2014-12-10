#ifdef WINDOWS_PLATFORM

#ifndef MPACK_WINDOWSKEYBOARDINTERFACE_HPP
#define MPACK_WINDOWSKEYBOARDINTERFACE_HPP

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
