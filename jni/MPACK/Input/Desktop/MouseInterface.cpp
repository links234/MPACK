#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "MouseInterface.hpp"

#include <cstring>

namespace MPACK
{
	namespace Input
	{
		MouseInterface::MouseInterface()
			: m_pCurrState(&m_stateBuffer1), m_pLastState(&m_stateBuffer2)
		{
		}

		MouseInterface::~MouseInterface()
		{
		}

		void MouseInterface::Reset()
		{
			memset(&m_stateBuffer1,0,sizeof(m_stateBuffer1));
			memset(&m_stateBuffer2,0,sizeof(m_stateBuffer2));
		}

		bool MouseInterface::ButtonDown(const MouseButton &button) const
		{
			switch(button)
			{
				case MBC_LEFT:
					return !m_pLastState->Button.Left && m_pCurrState->Button.Left;
				case MBC_MIDDLE:
					return !m_pLastState->Button.Middle && m_pCurrState->Button.Middle;
				case MBC_RIGHT:
					return !m_pLastState->Button.Right && m_pCurrState->Button.Right;
			}
			return false;
		}

		bool MouseInterface::ButtonUp(const MouseButton &button) const
		{
			switch(button)
			{
				case MBC_LEFT:
					return m_pLastState->Button.Left && !m_pCurrState->Button.Left;
				case MBC_MIDDLE:
					return m_pLastState->Button.Middle && !m_pCurrState->Button.Middle;
				case MBC_RIGHT:
					return m_pLastState->Button.Right && !m_pCurrState->Button.Right;
			}
			return false;
		}

		bool MouseInterface::ButtonPressed(const MouseButton &button) const
		{
			switch(button)
			{
				case MBC_LEFT:
					return m_pLastState->Button.Left && m_pCurrState->Button.Left;
				case MBC_MIDDLE:
					return m_pLastState->Button.Middle && m_pCurrState->Button.Middle;
				case MBC_RIGHT:
					return m_pLastState->Button.Right && m_pCurrState->Button.Right;
			}
			return false;
		}

		Math::Vector2f MouseInterface::GetPosition() const
		{
			return m_pCurrState->Pos;
		}

		bool MouseInterface::Moved() const
		{
			return m_pCurrState->Pos!=m_pLastState->Pos;
		}
	}
}

#endif

