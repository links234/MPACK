#ifdef ANDROID_PLATFORM

#ifndef ANDROIDTIMESERVICE_HPP
#define ANDROIDTIMESERVICE_HPP

#include "TimeService.hpp"

namespace Core
{
    class AndroidTimeService : public TimeService
    {
    public:
        AndroidTimeService();

        void Reset();
        void Update();

        double Now();
        float 	Elapsed();

    private:
        float mElapsed;
        double mLastTime;
    };
}
#endif

#endif
