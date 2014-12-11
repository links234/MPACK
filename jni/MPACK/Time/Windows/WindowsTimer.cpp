#ifdef WINDOWS_PLATFORM

#include "WindowsTimer.hpp"

#include <windows.h>

namespace MPACK
{
	namespace Time
	{
		unsigned int GetTicksCount()
		{
			SYSTEMTIME time;
			GetSystemTime(&time);
			return (time.wSecond * 1000) + time.wMilliseconds;
		}

		WindowsTimer::WindowsTimer()
			: m_currClock(0)
		{
		}

		WindowsTimer::~WindowsTimer()
		{
		}

		void WindowsTimer::Start()
		{
			m_currClock=GetTicksCount();
		}

		double WindowsTimer::Time() const
		{
			return (double)(GetTicksCount()-m_currClock)/1000.0;
		}
	}
}

#endif
