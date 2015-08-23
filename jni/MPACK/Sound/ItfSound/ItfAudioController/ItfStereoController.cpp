#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfStereoController.hpp"

#include "ItfSoundService.hpp"
#include "ItfAudioControllers.hpp"
#include "ItfGroupControllers.hpp"
#include "ItfOutputMixer.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		StereoController StereoController::s_sentinel(VolumeController::GetSentinel());

		StereoController::StereoController(VolumeController *pVolumeController)
			: m_pVolumeController(pVolumeController), m_enabled(false), m_position(0)
		{
		}

		StereoController::~StereoController()
		{
		}

		bool StereoController::IsSupported() const
		{
			return m_pVolumeController->IsSupported();
		}

		bool StereoController::IsEnabled() const
		{
			return m_enabled;
		}

		Core::ReturnValue StereoController::Enable()
		{
			return SetEnabled(true);
		}

		Core::ReturnValue StereoController::Disable()
		{
			return SetEnabled(false);
		}

		Core::ReturnValue StereoController::Toggle()
		{
			return SetEnabled(!m_enabled);
		}

		Core::ReturnValue StereoController::SetEnabled(bool enabled)
		{
			if(m_pVolumeController->SetEnabledStereo(enabled) == RETURN_VALUE_OK)
			{
				m_enabled=enabled;
				return RETURN_VALUE_OK;
			}
			return RETURN_VALUE_KO;
		}

		Core::ReturnValue StereoController::Set(int position)
		{
			if(m_pVolumeController->SetStereoPosition(position) == RETURN_VALUE_OK)
			{
				m_position=position;
				return RETURN_VALUE_OK;
			}
			return RETURN_VALUE_KO;
		}

		int StereoController::Get() const
		{
			return m_position;
		}

		StereoController* StereoController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
