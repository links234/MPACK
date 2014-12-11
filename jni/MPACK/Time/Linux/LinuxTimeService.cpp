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
			struct timeval t;
			gettimeofday(&t, NULL);

			unsigned long secs = t.tv_sec * 1000;
			secs += (t.tv_usec / 1000);
			return double(secs) / 1000.0;
		}

		float LinuxTimeService::Elapsed()
		{
			return mElapsed;
		}
	}
}

#endif

