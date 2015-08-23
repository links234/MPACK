#ifdef ANDROID_PLATFORM

#include "OSLESBassBoostController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		BassBoostController BassBoostController::s_sentinel;

		BassBoostController::BassBoostController()
			: m_interface(NULL), m_enabled(false), m_strength(0)
		{
		}

		BassBoostController::BassBoostController(SLObjectItf object)
			: m_interface(NULL), m_enabled(false), m_strength(0)
		{
			SLresult res = (*object)->GetInterface(object, SL_IID_BASSBOOST, &m_interface);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("BassBoostController(): BassBoostItf is not supported: res = %d",res);
				m_interface=NULL;
			}
		}

		BassBoostController::~BassBoostController()
		{
			m_interface=NULL;
		}

		bool BassBoostController::IsSupported() const
		{
			return m_interface!=NULL;
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
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetEnabled(m_interface, enabled);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("BassBoostController::SetEnable() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_enabled=enabled;
			return RETURN_VALUE_OK;
		}

		ReturnValue BassBoostController::SetStrength(SLpermille strength)
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetStrength(m_interface, strength);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("BassBoostController::SetStrength() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			m_strength=strength;
			return RETURN_VALUE_OK;
		}

		SLpermille BassBoostController::GetStrength() const
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
