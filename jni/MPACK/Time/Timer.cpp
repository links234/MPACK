#include "Timer.hpp"

#include "Types.hpp"
#include "WindowsTimer.hpp"
#include "AndroidTimer.hpp"
#include "LinuxTimer.hpp"

namespace MPACK
{
	namespace Time
	{
		Timer::Timer()
		{
		}

		Timer::~Timer()
		{
		}

		Timer* Timer::Create()
		{
			Timer *pTimer=NULL;
	#ifdef ANDROID_PLATFORM
		pTimer = (Timer*) new AndroidTimer();
	#elif	defined(WINDOWS_PLATFORM)
		pTimer = (Timer*) new WindowsTimer();
	#elif	defined(LINUX_PLATFORM)
		pTimer = (Timer*) new LinuxTimer();
	#endif
			return pTimer;
		}
	}
}
