#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfSoundService.hpp"

#include "Log.hpp"
#include "Global.hpp"
#include "ItfGroupControllers.hpp"
#include "ItfOutputMixer.hpp"
#include "ItfAudioPlayer.hpp"

using namespace MPACK::Core;
using namespace MPACK::Global;

namespace MPACK
{
	namespace Sound
	{
		SoundService::SoundService()
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
			return RETURN_VALUE_OK;
		}

		void SoundService::Stop()
		{
			LOGI("Stopping SoundService.");

			AudioPlayer::Cleanup();
			OutputMixer::Cleanup();
			GroupController::Cleanup();
		}
	}
}

#endif
