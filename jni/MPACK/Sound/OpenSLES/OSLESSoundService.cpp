#ifdef ANDROID_PLATFORM

#include "OSLESSoundService.hpp"

#include "Log.hpp"
#include "Global.hpp"
#include "OSLESGroupControllers.hpp"
#include "OSLESOutputMixer.hpp"
#include "OSLESAudioPlayer.hpp"

using namespace std;
using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		SoundService::SoundService()
		   : m_engineObj(NULL), m_engine(NULL)
		{
			LOGI("Creating SoundService.");
		}

		SoundService::~SoundService()
		{
			LOGI("Destroying SoundService.");
		}

		ReturnValue SoundService::Start()
		{
			LOGI("Starting SoundService.");

			SLresult res;
			const SLuint32      engineMixIIDCount = 0;
			const SLInterfaceID engineMixIIDs[]   = {};
			const SLboolean     engineMixReqs[]   = {};

			res = slCreateEngine(&m_engineObj, 0, NULL, engineMixIIDCount, engineMixIIDs, engineMixReqs);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SoundService::Start() at slCreateEngine");
				goto ERROR;
			}
			res = (*m_engineObj)->Realize(m_engineObj,SL_BOOLEAN_FALSE);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SoundService::Start() at (*m_engineObj)->Realize");
				goto ERROR;
			}
			res = (*m_engineObj)->GetInterface(m_engineObj, SL_IID_ENGINE, &m_engine);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("SoundService::Start() at (*m_engineObj)->GetInterface");
				goto ERROR;
			}

			if(!OutputMixer::GetOutputMixer())
			{
				goto FAIL;
			}

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("SoundService::Start() error: res = %d", res);
			goto ERROR_EXIT;

		FAIL:
			LOGE("SoundService::Start() failed");
			goto ERROR_EXIT;

		ERROR_EXIT:
			Stop();
			return RETURN_VALUE_KO;
		}

		void SoundService::Stop()
		{
			LOGI("Stopping SoundService.");

			AudioPlayer::Cleanup();
			OutputMixer::Cleanup();
			GroupController::Cleanup();

			if (m_engineObj != NULL)
			{
				(*m_engineObj)->Destroy(m_engineObj);
				m_engineObj = NULL;
				m_engine = NULL;
			}
		}

		SLEngineItf& SoundService::GetOpenSLEngine()
		{
			return m_engine;
		}
	}
}

#endif
