#ifdef ANDROID_PLATFORM

#include "OSLESSeekController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		SeekController SeekController::s_sentinel;

		SeekController::SeekController()
			: m_interface(NULL), m_looping(false)
		{
		}

		SeekController::SeekController(SLObjectItf object)
			: m_interface(NULL), m_looping(false)
		{
			SLresult res = (*object)->GetInterface(object, SL_IID_SEEK, &m_interface);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SeekController(): SeekItf is not supported: res = %d",res);
				m_interface=NULL;
			}
		}

		SeekController::~SeekController()
		{
			m_interface=NULL;
		}

		bool SeekController::IsSupported() const
		{
			return m_interface!=NULL;
		}

		ReturnValue SeekController::SetPosition(SLmillisecond position)
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetPosition(m_interface, position, SL_SEEKMODE_FAST);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SeekController::SetPosition() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
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
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetLoop(m_interface, enabled, 0, SL_TIME_UNKNOWN);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SeekController::SetEnabledLooping() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
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
