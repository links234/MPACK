#include "Platform.hpp"

#ifdef ANDROID_PLATFORM

#include "AndroidTimer.hpp"

#include "Log.hpp"

#include <time.h>
#include <cstdlib>

namespace Core
{
	AndroidTimeService::AndroidTimeService()
		: m_lastTime(0)
    {
    }

	AndroidTimeService::~AndroidTimeService()
	{
	}

    void AndroidTimeService::Start()
    {
        timespec lTimeVal;
        clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
        m_lastTime = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
    }

    float AndroidTimeService::Time() const
    {
    	timespec lTimeVal;
		clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
		double currTime = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
        return (float)(currTime-m_lastTime);
    }
}

#endif

