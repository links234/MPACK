#ifdef ANDROID_PLATFORM

#include "AndroidTimer.hpp"

#include "Log.hpp"

#include <time.h>
#include <cstdlib>

namespace MPACK
{
	namespace Time
	{
		AndroidTimer::AndroidTimer()
			: m_lastTime(0)
		{
		}

		AndroidTimer::~AndroidTimer()
		{
		}

		void AndroidTimer::Start()
		{
			timespec lTimeVal;
			clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
			m_lastTime = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
		}

		double AndroidTimer::Time() const
		{
			timespec lTimeVal;
			clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
			double currTime = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
			return currTime-m_lastTime;
		}
	}
}

#endif

