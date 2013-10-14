#include "Timer.hpp"

#include "Types.hpp"
#include "WindowsTimer.hpp"
#include "AndroidTimer.hpp"

namespace Core
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
#endif
    	return pTimer;
    }
}
