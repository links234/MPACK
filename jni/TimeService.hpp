#ifndef TIMESERVICE_HPP
#define TIMESERVICE_HPP

#include "Types.hpp"

#include <time.h>

namespace Core
{
    class TimeService
    {
    public:
        TimeService();

        void Reset();
        void Update();

        double Now();
        float Elapsed();

    private:
        float mElapsed;
        double mLastTime;
    };
}
#endif
