#ifdef OSX_PLATFORM

#include "OSXKeyboardInterface.hpp"

#include "Types.hpp"

namespace MPACK
{
	namespace Input
	{
		OSXKeyboardInterface::OSXKeyboardInterface()
		{
		}

		OSXKeyboardInterface::~OSXKeyboardInterface()
		{
		}

		void OSXKeyboardInterface::Update()
		{
			memcpy(m_lastState,m_currState,sizeof(m_state1));
		}

		KeyCode OSXKeyboardInterface::TranslateCode(const int &code)
		{
			switch(code)
			{
				//case VK_ESCAPE:
				//	return KC_ESCAPE;
				//case VK_SPACE:
				//	return KC_SPACE;
				case 'W':
					return KC_W;
				case 'A':
					return KC_A;
				case 'S':
					return KC_S;
				case 'D':
					return KC_D;
			}
			return KC_INVALID;
		}
	}
}

#endif
