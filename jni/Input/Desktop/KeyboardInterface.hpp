#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef KEYBOARDINTERFACE_HPP
#define KEYBOARDINTERFACE_HPP

#include "Types.hpp"

namespace Core
{
	enum KeyCode
	{
		KC_INVALID,
		KC_UP,
		KC_DOWN,
		KC_LEFT,
		KC_RIGHT,
		KC_SPACE,
		KC_ESCAPE,
		KC_W,
		KC_A,
		KC_S,
		KC_D,
		KC_MAX_KEYS
	};

	class KeyboardInterface
	{
	public:
		KeyboardInterface();
		virtual ~KeyboardInterface();

		virtual void Update() = 0;

		void Reset();

		bool KeyDown(const KeyCode &key);
		bool KeyUp(const KeyCode &key);
		bool KeyPressed(const KeyCode &key);

		void HandleKeyDown(const KeyCode &key);
		void HandleKeyUp(const KeyCode &key);

		virtual KeyCode TranslateCode(const int &code) = 0;

	protected:
		BYTE		m_state1[KC_MAX_KEYS];
		BYTE		m_state2[KC_MAX_KEYS];
		BYTE		*m_currState;
		BYTE		*m_lastState;
	};
}

#endif

#endif
