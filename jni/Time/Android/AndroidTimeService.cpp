#ifdef ANDROID_PLATFORM

#include "AndroidTimeService.hpp"

#include "Log.hpp"

#include <time.h>
#include <cstdlib>

namespace Core
{
	AndroidTimeService::AndroidTimeService() :
        mElapsed(0.0f),
        mLastTime(0.0f)
    {
    }

    void AndroidTimeService::Reset()
    {
        LOGI("Resetting TimeService.");
        mElapsed = 0.0f;
        mLastTime = Now();
    }

    void AndroidTimeService::Update()
    {
        double lCurrentTime = Now();
        mElapsed = (lCurrentTime - mLastTime);
        mLastTime = lCurrentTime;
    }

    double AndroidTimeService::Now()
    {
        timespec lTimeVal;
        clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
        return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
    }

    float AndroidTimeService::Elapsed()
    {
        return mElapsed;
    }
}

#endif

