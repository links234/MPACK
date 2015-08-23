#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfSeekController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		SeekController SeekController::s_sentinel;

		SeekController::SeekController()
			: m_looping(false)
		{
		}

		SeekController::~SeekController()
		{
		}

		bool SeekController::IsSupported() const
		{
			return true;
		}

		ReturnValue SeekController::SetPosition(int position)
		{
			return RETURN_VALUE_OK;
		}

		bool SeekController::IsLoopingEnabled() const
		{
			return m_looping;
		}

		ReturnValue SeekController::EnableLooping()
		{
			return SetEnabledLooping(true);
		}

		ReturnValue SeekController::DisableLooping()
		{
			return SetEnabledLooping(false);
		}

		ReturnValue SeekController::ToggleLooping()
		{
			return SetEnabledLooping(!m_looping);
		}

		ReturnValue SeekController::SetEnabledLooping(bool enabled)
		{
			m_looping = enabled;
			return RETURN_VALUE_OK;
		}

		SeekController* SeekController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
