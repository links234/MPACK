#ifdef OSX_PLATFORM

#include "OSXTimeService.hpp"

#include "OSXTime.hpp"
#include "Debug.hpp"

namespace MPACK
{
	namespace Time
	{
		OSXTimeService::OSXTimeService() :
			mElapsed(0.0f),
			mLastTime(0.0f)
		{
		}

		void OSXTimeService::Reset()
		{
			LOGI("Resetting TimeService.");
			mElapsed = 0.0f;
			mLastTime = Now();
		}

		void OSXTimeService::Update()
		{
			double lCurrentTime = Now();
			mElapsed = (lCurrentTime - mLastTime);
			mLastTime = lCurrentTime;
		}

		double OSXTimeService::Now()
		{
			return (double)(mach_absolute_time()) * GetConversionFactor() * 1e-9;
		}

		float OSXTimeService::Elapsed()
		{
			return mElapsed;
		}
	}
}

#endif
