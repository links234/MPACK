#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_MOUSEINTERFACE_HPP
#define MPACK_MOUSEINTERFACE_HPP

#include "MouseState.hpp"

namespace MPACK
{
	namespace Input
	{
		enum MouseButton
		{
			MBC_LEFT,
			MBC_MIDDLE,
			MBC_RIGHT
		};

		class MouseInterface
		{
		public:
			MouseInterface();
			virtual ~MouseInterface();

			virtual void Update() = 0;

			void Reset();

			bool ButtonDown(const MouseButton &button) const;
			bool ButtonUp(const MouseButton &button) const;
			bool ButtonPressed(const MouseButton &button) const;

			Math::Vector2f GetPosition() const;

			bool Moved() const;

		protected:
			MouseState 	*m_pCurrState;
			MouseState 	*m_pLastState;
			MouseState 	m_stateBuffer1;
			MouseState 	m_stateBuffer2;
		};
	}
}

#endif

#endif
