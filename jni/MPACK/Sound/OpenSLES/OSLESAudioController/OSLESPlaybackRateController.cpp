#ifdef ANDROID_PLATFORM

#include "OSLESPlaybackRateController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PlaybackRateController PlaybackRateController::s_sentinel;

		PlaybackRateController::PlaybackRateController()
			: m_interface(NULL), m_value(1.0), m_minValue(1.0), m_maxValue(1.0)
		{
		}

		PlaybackRateController::PlaybackRateController(SLObjectItf object)
			: m_interface(NULL), m_value(1.0), m_minValue(1.0), m_maxValue(1.0)
		{
			SLresult res = (*object)->GetInterface(object, SL_IID_PLAYBACKRATE, &m_interface);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlaybackRateController(): PlaybackRateItf is not supported: res = %d",res);
				m_interface=NULL;
			}
			else
			{
				m_minValue=0.5;
				m_maxValue=2.0;

				res = (*m_interface)->SetPropertyConstraints(m_interface, SL_RATEPROP_NOPITCHCORAUDIO);
				if(res != SL_RESULT_SUCCESS)
				{
					LOGE("PlaybackRateController() at (*m_audioPlaybackRate)->SetPropertyConstraints error: res = %d",res);
				}
			}
		}

		PlaybackRateController::~PlaybackRateController()
		{
			m_interface=NULL;
		}

		bool PlaybackRateController::IsSupported() const
		{
			return m_interface!=NULL;
		}

		ReturnValue PlaybackRateController::Set(double value)
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}

			value = Math::Misc<double>::Clamp(value,m_minValue,m_maxValue);

			SLresult res = (*m_interface)->SetRate(m_interface, (SLpermille)(value*1000));
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlaybackRateController::Set() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_value=value;
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
