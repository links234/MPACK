#ifdef LINUX_PLATFORM

#include "LinuxTimer.hpp"

#include <sys/time.h>

#define NULL 0

namespace MPACK
{
	namespace Time
	{
		unsigned int GetTicksCount()
		{
			struct timeval t;
			gettimeofday(&t, NULL);

			unsigned long secs = t.tv_sec * 1000;
			secs += (t.tv_usec / 1000);
			return secs;
		}

		LinuxTimer::LinuxTimer()
			: m_currClock(0)
		{
		}

		LinuxTimer::~LinuxTimer()
		{
		}

		void LinuxTimer::Start()
		{
			m_currClock=GetTicksCount();
		}

		double LinuxTimer::Time() const
		{
			return (double)(GetTicksCount()-m_currClock)/1000.0;
		}
	}
}

#endif
