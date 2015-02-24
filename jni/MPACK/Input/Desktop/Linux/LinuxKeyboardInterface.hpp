#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXKEYBOARDINTERFACE_HPP
#define MPACK_LINUXKEYBOARDINTERFACE_HPP

#include "KeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
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
}

#endif

#endif
