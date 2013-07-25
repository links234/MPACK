#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#include "WindowsTimer.hpp"

namespace Core
{
	WindowsTimer::WindowsTimer()
		: m_currClock(0)
	{
	}

	WindowsTimer::~WindowsTimer()
	{
	}

	void WindowsTimer::Start()
	{
		m_currClock=clock();
	}

	double WindowsTimer::Time() const
	{
		return (double)(clock()-m_currClock)/(double)(CLOCKS_PER_SEC);
	}
}

#endif
