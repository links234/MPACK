#ifdef LINUX_PLATFORM

#ifndef LINUXTIMER_HPP
#define LINUXTIMER_HPP

#include "Timer.hpp"

#include <ctime>

namespace Core
{
    class LinuxTimer : public Timer
    {
    public:
    	LinuxTimer();
    	virtual ~LinuxTimer();

    	virtual void Start();
    	virtual double Time() const;

    private:
    	clock_t	m_currClock;
    };
}

#endif

#endif
