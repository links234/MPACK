#ifdef LINUX_PLATFORM

#include "LinuxTimeService.hpp"

#include "Log.hpp"

#include <ctime>

namespace Core
{
	LinuxTimeService::LinuxTimeService() :
        mElapsed(0.0f),
        mLastTime(0.0f)
    {
    }

    void LinuxTimeService::Reset()
    {
        LOGI("Resetting TimeService.");
        mElapsed = 0.0f;
        mLastTime = Now();
    }

    void LinuxTimeService::Update()
    {
        double lCurrentTime = Now();
        mElapsed = (lCurrentTime - mLastTime);
        mLastTime = lCurrentTime;
    }

    double LinuxTimeService::Now()
    {
        return (double)(clock())/(double)(CLOCKS_PER_SEC);
    }

    float LinuxTimeService::Elapsed()
    {
        return mElapsed;
    }
}

#endif

