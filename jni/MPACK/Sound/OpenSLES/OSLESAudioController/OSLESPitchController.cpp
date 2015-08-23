#ifdef ANDROID_PLATFORM

#include "OSLESPitchController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PitchController PitchController::s_sentinel;

		PitchController::PitchController()
			: m_interface(NULL), m_value(1000), m_minValue(1000), m_maxValue(1000)
		{
		}

		PitchController::PitchController(SLObjectItf object)
			: m_interface(NULL), m_value(1000), m_minValue(1000), m_maxValue(1000)
		{
			SLresult res = (*object)->GetInterface(object, SL_IID_PITCH, &m_interface);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PitchController(): PitchItf is not supported: res = %d",res);
				m_interface=NULL;
			}
			else
			{
				SLresult res = (*m_interface)->GetPitchCapabilities(m_interface, &m_minValue, &m_maxValue);
				if (res == SL_RESULT_SUCCESS)
				{
					LOGE("PitchController() at (*m_interface)->GetPitchCapabilities: res = %d",res);
				}
			}
		}

		PitchController::~PitchController()
		{
			m_interface=NULL;
		}

		bool PitchController::IsSupported() const
		{
			return m_interface!=NULL;
		}

		ReturnValue PitchController::Set(SLpermille value)
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			value=Math::Misc<SLpermille>::Clamp(value,m_minValue,m_maxValue);
			SLresult res = (*m_interface)->SetPitch(m_interface, value);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PitchController::Set() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_value=value;
			return RETURN_VALUE_OK;
		}

		SLpermille PitchController::Get() const
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
