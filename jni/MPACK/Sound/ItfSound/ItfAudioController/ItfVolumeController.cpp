#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfVolumeController.hpp"

#include "ItfStereoController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		VolumeController VolumeController::s_sentinel;

		VolumeController::VolumeController()
			: m_pStereoController(StereoController::GetSentinel()),
			  m_muted(false), m_volume(100.0f)
		{
			m_pStereoController = new StereoController(this);
		}

		VolumeController::~VolumeController()
		{
			delete m_pStereoController;
		}

		bool VolumeController::IsSupported() const
		{
			return true;
		}

		bool VolumeController::IsMuted() const
		{
			return m_muted;
		}

		ReturnValue VolumeController::ToggleMute()
		{
			return SetMute(!m_muted);
		}

		ReturnValue VolumeController::Mute()
		{
			return SetMute(true);
		}

		ReturnValue VolumeController::Unmute()
		{
			return SetMute(false);
		}

		ReturnValue VolumeController::SetMute(bool mute)
		{
			m_muted=mute;
			return RETURN_VALUE_OK;
		}

		ReturnValue VolumeController::Set(double linear)
		{
			m_volume=linear;
			return RETURN_VALUE_OK;
		}

		StereoController* VolumeController::Stereo() const
		{
			return m_pStereoController;
		}

		VolumeController* VolumeController::GetSentinel()
		{
			return &s_sentinel;
		}

		ReturnValue VolumeController::SetEnabledStereo(bool enabled)
		{
			return RETURN_VALUE_OK;
		}

		ReturnValue VolumeController::SetStereoPosition(int stereoPosition)
		{
			return RETURN_VALUE_OK;
		}
	}
}

#endif
