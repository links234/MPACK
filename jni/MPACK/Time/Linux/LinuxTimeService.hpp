#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXTIMESERVICE_HPP
#define MPACK_LINUXTIMESERVICE_HPP

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
