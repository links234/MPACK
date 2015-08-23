#ifdef ANDROID_PLATFORM

#include "OSLESPlayController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PlayController PlayController::s_sentinel;

		PlayController::PlayController()
			: m_interface(NULL)
		{
		}

		PlayController::PlayController(SLObjectItf object)
			: m_interface(NULL)
		{
			SLresult res = (*object)->GetInterface(object, SL_IID_PLAY, &m_interface);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController(): PlayItf is not supported: res = %d",res);
				m_interface=NULL;
			}
		}

		PlayController::~PlayController()
		{
			m_interface=NULL;
		}

		bool PlayController::IsSupported() const
		{
			return m_interface!=NULL;
		}

		ReturnValue PlayController::Start()
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetPlayState(m_interface,SL_PLAYSTATE_STOPPED);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::Start() error at SL_PLAYSTATE_STOPPED: res = %d",res);
				return RETURN_VALUE_KO;
			}
			res = (*m_interface)->SetPlayState(m_interface,SL_PLAYSTATE_PLAYING);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::Start() error at SL_PLAYSTATE_PLAYING: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue PlayController::Resume()
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetPlayState(m_interface,SL_PLAYSTATE_PLAYING);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::Resume() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue PlayController::Pause()
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetPlayState(m_interface,SL_PLAYSTATE_PAUSED);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::Pause() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		ReturnValue PlayController::Stop()
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLresult res = (*m_interface)->SetPlayState(m_interface,SL_PLAYSTATE_STOPPED);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::Stop() error: res = %d",res);
				return RETURN_VALUE_KO;
			}
			return RETURN_VALUE_OK;
		}

		SLmillisecond PlayController::GetPosition()
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLmillisecond position;
			SLresult res = (*m_interface)->GetPosition(m_interface, &position);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::GetPosition() error: res = %d",res);
				return 0;
			}
			return position;
		}

		SLmillisecond PlayController::GetDuration()
		{
			if(m_interface==NULL)
			{
				return RETURN_VALUE_OK;
			}
			SLmillisecond duration;
			SLresult res = (*m_interface)->GetDuration(m_interface, &duration);
			if (res != SL_RESULT_SUCCESS)
			{
				LOGE("PlayController::GetDuration() error: res = %d",res);
				return 0;
			}
			return duration;
		}

		PlayController* PlayController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
