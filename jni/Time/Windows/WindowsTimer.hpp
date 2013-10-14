#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSTIMER_HPP
#define WINDOWSTIMER_HPP

#include "Timer.hpp"

#include <ctime>

namespace Core
{
    class WindowsTimer : public Timer
    {
    public:
    	WindowsTimer();
    	virtual ~WindowsTimer();

    	virtual void Start();
    	virtual double Time() const;

    private:
    	clock_t	m_currClock;
    };
}

#endif

#endif
