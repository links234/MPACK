#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfPitchController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PitchController PitchController::s_sentinel;

		PitchController::PitchController()
			: m_value(1000), m_minValue(1000), m_maxValue(1000)
		{
		}

		PitchController::~PitchController()
		{
		}

		bool PitchController::IsSupported() const
		{
			return true;
		}

		ReturnValue PitchController::Set(int value)
		{
			m_value=Math::Misc<int>::Clamp(value,m_minValue,m_maxValue);
			return RETURN_VALUE_OK;
		}

		int PitchController::Get() const
		{
			return m_value;
		}

		PitchController* PitchController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
