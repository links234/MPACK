#ifdef WINDOWS_PLATFORM

#ifndef WINDOWSTIMER_HPP
#define WINDOWSTIMER_HPP

#include "Timer.hpp"

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
    	unsigned int m_currClock;
    };
}

#endif

#endif
