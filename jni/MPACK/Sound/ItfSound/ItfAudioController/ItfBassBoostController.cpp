#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfBassBoostController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		BassBoostController BassBoostController::s_sentinel;

		BassBoostController::BassBoostController()
			: m_enabled(false), m_strength(0)
		{
		}

		BassBoostController::~BassBoostController()
		{
		}

		bool BassBoostController::IsSupported() const
		{
			return true;
		}

		bool BassBoostController::IsEnabled() const
		{
			return m_enabled;
		}

		ReturnValue BassBoostController::Enable()
		{
			return SetEnabled(true);
		}

		ReturnValue BassBoostController::Disable()
		{
			return SetEnabled(false);
		}

		ReturnValue BassBoostController::Toggle()
		{
			return SetEnabled(!m_enabled);
		}

		ReturnValue BassBoostController::SetEnabled(bool enabled)
		{
			m_enabled=enabled;
			return RETURN_VALUE_OK;
		}

		ReturnValue BassBoostController::SetStrength(int strength)
		{
			m_strength=strength;
			return RETURN_VALUE_OK;
		}

		int BassBoostController::GetStrength() const
		{
			return m_strength;
		}

		BassBoostController* BassBoostController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
