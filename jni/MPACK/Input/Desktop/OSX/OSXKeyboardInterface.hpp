#ifdef OSX_PLATFORM

#ifndef MPACK_OSXKEYBOARDINTERFACE_HPP
#define MPACK_OSXKEYBOARDINTERFACE_HPP

#include "KeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		class OSXKeyboardInterface : public KeyboardInterface
		{
		public:
			OSXKeyboardInterface();
			~OSXKeyboardInterface();

			void Update();

			KeyCode TranslateCode(const int &code);
		};
	}
}

#endif

#endif
