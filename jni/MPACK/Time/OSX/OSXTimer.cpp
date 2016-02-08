#ifdef OSX_PLATFORM

#include "OSXTimer.hpp"

#include "Types.hpp"
#include "OSXTime.hpp"

namespace MPACK
{
	namespace Time
	{
		OSXTimer::OSXTimer()
			: m_lastTime(0)
		{
		}

		OSXTimer::~OSXTimer()
		{
		}

		void OSXTimer::Start()
		{
			m_lastTime = (double)(mach_absolute_time()) * GetConversionFactor() * 1e-9;
		}

		double OSXTimer::Time() const
		{
			double currTime = (double)(mach_absolute_time()) * GetConversionFactor() * 1e-9;
			return currTime-m_lastTime;
		}
	}
}

#endif
