#ifdef LINUX_PLATFORM

#include "LinuxTimeService.hpp"

#include "Debug.hpp"

#include <sys/time.h>
#include <ctime>

namespace MPACK
{
	namespace Time
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
			timespec lTimeVal;
			clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
			return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
		}

		float LinuxTimeService::Elapsed()
		{
			return mElapsed;
		}
	}
}

#endif

