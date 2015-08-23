#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfPlayController.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PlayController PlayController::s_sentinel;

		PlayController::PlayController()
		{
		}

		PlayController::~PlayController()
		{
		}

		bool PlayController::IsSupported() const
		{
			return true;
		}

		ReturnValue PlayController::Start()
		{
			return RETURN_VALUE_OK;
		}

		ReturnValue PlayController::Resume()
		{
			return RETURN_VALUE_OK;
		}

		ReturnValue PlayController::Pause()
		{
			return RETURN_VALUE_OK;
		}

		ReturnValue PlayController::Stop()
		{
			return RETURN_VALUE_OK;
		}

		int PlayController::GetPosition()
		{
			return 0;
		}

		int PlayController::GetDuration()
		{
			return 0;
		}

		PlayController* PlayController::GetSentinel()
		{
			return &s_sentinel;
		}
	}
}

#endif
