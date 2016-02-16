#ifdef OSX_PLATFORM

#include "OSXTime.hpp"

namespace MPACK
{
  namespace Time
  {
    double GetConversionFactor()
    {
      static double m_conversionFactor = 0.0;
      if (m_conversionFactor == 0.0)
      {
        mach_timebase_info_data_t timebase;
  		  mach_timebase_info(&timebase);
  		  m_conversionFactor = (double)timebase.numer / (double)timebase.denom;
      }
      return m_conversionFactor;
    }
  }
}

#endif
