#ifdef OSX_PLATFORM

#ifndef MPACK_OSXTIME_HPP
#define MPACK_OSXTIME_HPP

#include <mach/mach_time.h>

namespace MPACK
{
  namespace Time
  {
    double GetConversionFactor();
  }
}

#endif

#endif
