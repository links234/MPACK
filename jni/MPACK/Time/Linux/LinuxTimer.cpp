#ifdef LINUX_PLATFORM

#include "LinuxTimer.hpp"

#include "Types.hpp"

namespace MPACK
{
	namespace Time
	{
		LinuxTimer::LinuxTimer()
			: m_lastTime(0)
		{
		}

		LinuxTimer::~LinuxTimer()
		{
		}

		void LinuxTimer::Start()
		{
			timespec lTimeVal;
			clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
			m_lastTime = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
		}

		double LinuxTimer::Time() const
		{
			timespec lTimeVal;
			clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
			double currTime = lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
			return currTime-m_lastTime;
		}
	}
}

#endif
