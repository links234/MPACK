#include "Timer.hpp"

#include "Types.hpp"
#include "WindowsTimer.hpp"
#include "AndroidTimer.hpp"
#include "LinuxTimer.hpp"
#include "OSXTimer.hpp"

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
#if defined(ANDROID_PLATFORM)
			pTimer = (Timer*) new AndroidTimer();
#elif	defined(WINDOWS_PLATFORM)
			pTimer = (Timer*) new WindowsTimer();
#elif	defined(LINUX_PLATFORM)
			pTimer = (Timer*) new LinuxTimer();
#elif defined(OSX_PLATFORM)
			pTimer = (Timer*) new OSXTimer();
#endif
			return pTimer;
		}
	}
}
