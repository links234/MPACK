#ifdef LINUX_PLATFORM

#include "LinuxKeyboardInterface.hpp"

#include "Types.hpp"

namespace MPACK
{
	namespace Input
	{
		LinuxKeyboardInterface::LinuxKeyboardInterface()
		{
		}

		LinuxKeyboardInterface::~LinuxKeyboardInterface()
		{
		}

		void LinuxKeyboardInterface::Update()
		{
			memcpy(m_lastState,m_currState,sizeof(m_state1));
		}

		KeyCode LinuxKeyboardInterface::TranslateCode(const int &code)
		{
			switch(code)
			{
				case XK_Escape:
					return KC_ESCAPE;
				case XK_space:
					return KC_SPACE;
				case XK_w:
					return KC_W;
				case XK_a:
					return KC_A;
				case XK_s:
					return KC_S;
				case XK_d:
					return KC_D;
			}
			return KC_INVALID;
		}
	}
}

#endif

