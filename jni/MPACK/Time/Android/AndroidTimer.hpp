#ifdef ANDROID_PLATFORM

#ifndef MPACK_ANDROIDTIMER_HPP
#define MPACK_ANDROIDTIMER_HPP

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
