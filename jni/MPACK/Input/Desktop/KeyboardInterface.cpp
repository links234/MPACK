#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "KeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		KeyboardInterface::KeyboardInterface()
			: m_currState(m_state1), m_lastState(m_state2)
		{
		}

		KeyboardInterface::~KeyboardInterface()
		{
		}

		void KeyboardInterface::Reset()
		{
			memset(m_state1,0,sizeof(m_state1));
			memset(m_state2,0,sizeof(m_state2));
		}

		bool KeyboardInterface::KeyDown(const KeyCode &key) const
		{
			return (!m_lastState[key] && m_currState[key]);
		}

		bool KeyboardInterface::KeyUp(const KeyCode &key) const
		{
			return (m_lastState[key] && !m_currState[key]);
		}

		bool KeyboardInterface::KeyPressed(const KeyCode &key) const
		{
			return (m_lastState[key] && m_currState[key]);
		}

		void KeyboardInterface::HandleKeyDown(const KeyCode &key)
		{
			if(key!=KC_INVALID && key!=KC_MAX_KEYS)
			{
				m_currState[key]=1;
			}
		}

		void KeyboardInterface::HandleKeyUp(const KeyCode &key)
		{
			if(key!=KC_INVALID && key!=KC_MAX_KEYS)
			{
				m_currState[key]=0;
			}
		}
	}
}

#endif

