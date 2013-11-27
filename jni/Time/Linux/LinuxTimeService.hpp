#ifdef LINUX_PLATFORM

#ifndef LINUXTIMESERVICE_HPP
#define LINUXTIMESERVICE_HPP

#include "TimeService.hpp"

namespace Core
{
    class LinuxTimeService : public TimeService
    {
    public:
        LinuxTimeService();

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
