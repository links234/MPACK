#include "VolumeController.hpp"

using namespace MPACK::Core;


namespace MPACK
{
	namespace Sound
	{
		VolumeController VolumeController::s_sentinel;

		VolumeController::VolumeController()
			: m_interface(NULL), m_muted(false), m_volume(1.0), m_mBMinVolume(0), m_mBMaxVolume(0),
			  m_stereoEnabled(false), m_stereoPosition(0)
		{
		}

		VolumeController::VolumeController(SLObjectItf object)
			: m_interface(NULL), m_muted(false), m_volume(1.0), m_mBMinVolume(0), m_mBMaxVolume(0),
			  m_stereoEnabled(false), m_stereoPosition(0)
		{
			SLresult res = (*object)->GetInterface(object, SL_IID_VOLUME, &m_interface);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("VolumeController(): VolumeItf is not supported: res = %d",res);
				m_interface=NULL;
			}
			else
			{
				m_mBMinVolume = SL_MILLIBEL_MIN;
				m_mBMaxVolume = SL_MILLIBEL_MIN;
				res = (*m_interface)->GetMaxVolumeLevel(m_interface, &m_mBMaxVolume);
				if (res != SL_RESULT_SUCCESS)
				{
					LOGE("VolumeController() error at (*m_interface)->GetMaxVolumeLevel: res = %d ",res);
					m_interface=NULL;
				}
			}
		}
		VolumeController::~VolumeController()
		{
			m_interface=NULL;
		}

		bool VolumeController::IsSupported() const
		{
			return m_interface!=NULL;
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

		ReturnValue VolumeController::SetMute(SLboolean mute)
		{
			SLresult res = (*m_interface)->SetMute(m_interface,mute);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("VolumeController::SetMute() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_muted=mute;
			return RETURN_VALUE_OK;
		}

		ReturnValue VolumeController::Set(double linear)
		{
			int dBVolume = 20*log10(linear);
			SLmillibel mBVolume = dBVolume*100;

			mBVolume = Math::Misc<SLmillibel>::Clamp(mBVolume,m_mBMinVolume,m_mBMaxVolume);

			SLresult res = (*m_interface)->SetVolumeLevel(m_interface, mBVolume);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetVolume() error: res = %d",res);
				return RETURN_VALUE_KO;
			}

			m_volume=linear;
			return RETURN_VALUE_OK;
		}

		double VolumeController::Get() const
		{
			return m_volume;
		}

		bool VolumeController::IsStereoEnabled() const
		{
			return m_stereoEnabled;
		}

		ReturnValue VolumeController::EnableStereo()
		{
			return SetEnabledStereo(true);
		}

		ReturnValue VolumeController::DisableStereo()
		{
			return SetEnabledStereo(false);
		}

		ReturnValue VolumeController::ToggleStereo()
		{
			return SetEnabledStereo(!m_stereoEnabled);
		}

		ReturnValue VolumeController::SetEnabledStereo(bool enabled)
		{
			SLresult res = (*m_interface)->EnableStereoPosition(m_interface, enabled);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetEnableStereo() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_stereoEnabled=enabled;
			return RETURN_VALUE_OK;
		}

		ReturnValue VolumeController::SetStereoPosition(SLpermille stereoPosition)
		{
			SLresult res = (*m_interface)->SetStereoPosition(m_interface, stereoPosition);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("AudioPlayer::SetStereoPosition() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_stereoPosition=stereoPosition;
			return RETURN_VALUE_OK;
		}

		SLpermille VolumeController::GetStereoPosition() const
		{
			return m_stereoPosition;
		}

		VolumeController* VolumeController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}
