#ifdef LINUX_PLATFORM

#include "LinuxTimer.hpp"

namespace Core
{
	LinuxTimer::LinuxTimer()
		: m_currClock(0)
	{
	}

	LinuxTimer::~LinuxTimer()
	{
	}

	void LinuxTimer::Start()
	{
		m_currClock=clock();
	}

	double LinuxTimer::Time() const
	{
		return (double)(clock()-m_currClock)/(double)(CLOCKS_PER_SEC);
	}
}

#endif
