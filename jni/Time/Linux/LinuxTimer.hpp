#ifdef LINUX_PLATFORM

#ifndef LINUXTIMER_HPP
#define LINUXTIMER_HPP

#include "Timer.hpp"

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
    	unsigned int	m_currClock;
    };
}

#endif

#endif
