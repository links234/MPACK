#include "Platform.hpp"

#ifdef ANDROID_PLATFORM

#ifndef ANDROIDTIMER_HPP
#define ANDROIDTIMER_HPP

#include "Timer.hpp"

namespace Core
{
    class AndroidTimer : public Timer
    {
    public:
    	AndroidTimer();
    	virtual ~AndroidTimer();

        virtual void Start();
        virtual double Time() const;

    private:
        double m_lastTime;
    };
}
#endif

#endif
