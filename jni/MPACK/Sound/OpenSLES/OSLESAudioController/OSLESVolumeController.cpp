#ifdef ANDROID_PLATFORM

#include "OSLESVolumeController.hpp"

#include "OSLESStereoController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		VolumeController VolumeController::s_sentinel;

		VolumeController::VolumeController()
			: m_interface(NULL), m_muted(false), m_volume(1.0), m_mBMinVolume(0), m_mBMaxVolume(0),
			  m_pStereoController(StereoController::GetSentinel())
		{
		}

		VolumeController::VolumeController(SLObjectItf object)
			: m_interface(NULL), m_muted(false), m_volume(1.0), m_mBMinVolume(0), m_mBMaxVolume(0),
			  m_pStereoController(StereoController::GetSentinel())
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

				m_pStereoController = new StereoController(this);
			}
		}
		VolumeController::~VolumeController()
		{
			delete m_pStereoController;

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
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
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
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			int dBVolume = 20*log10(linear);
			SLmillibel mBVolume = dBVolume*100;

			mBVolume = Math::Misc<SLmillibel>::Clamp(mBVolume,m_mBMinVolume,m_mBMaxVolume);

			SLresult res = (*m_interface)->SetVolumeLevel(m_interface, mBVolume);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("VolumeController::Set() error: res = %d",res);
				return RETURN_VALUE_KO;
			}

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
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->EnableStereoPosition(m_interface, enabled);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("VolumeController::SetEnableStereo() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue VolumeController::SetStereoPosition(SLpermille stereoPosition)
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetStereoPosition(m_interface, stereoPosition);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("VolumeController::SetStereoPosition() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}
	}
}

#endif
