#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfPlaybackRateController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PlaybackRateController PlaybackRateController::s_sentinel;

		PlaybackRateController::PlaybackRateController()
			: m_value(1.0), m_minValue(0.5), m_maxValue(2.5)
		{
		}

		PlaybackRateController::~PlaybackRateController()
		{
		}

		bool PlaybackRateController::IsSupported() const
		{
			return true;
		}

		ReturnValue PlaybackRateController::Set(double value)
		{
			m_value = Math::Misc<double>::Clamp(value,m_minValue,m_maxValue);
			return RETURN_VALUE_OK;
		}

		double PlaybackRateController::Get() const
		{
			return m_value;
		}

		PlaybackRateController* PlaybackRateController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
