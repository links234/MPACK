#include "TimeService.hpp"
#include "Log.hpp"

#include <cstdlib>

namespace Core
{
    TimeService::TimeService() :
        mElapsed(0.0f),
        mLastTime(0.0f)
    {
    	srand(time(NULL));
    }

    void TimeService::Reset()
    {
        LOGI("Resetting TimeService.");
        mElapsed = 0.0f;
        mLastTime = Now();
    }

    void TimeService::Update()
    {
        double lCurrentTime = Now();
        mElapsed = (lCurrentTime - mLastTime);
        mLastTime = lCurrentTime;
    }

    double TimeService::Now()
    {
        timespec lTimeVal;
        clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
        return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
    }

    float TimeService::Elapsed()
    {
        return mElapsed;
    }
}
