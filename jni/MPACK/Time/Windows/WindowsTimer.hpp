#ifdef WINDOWS_PLATFORM

#ifndef MPACK_WINDOWSTIMER_HPP
#define MPACK_WINDOWSTIMER_HPP

#include "Timer.hpp"

namespace MPACK
{
	namespace Time
	{
		class WindowsTimer : public Timer
		{
		public:
			WindowsTimer();
			virtual ~WindowsTimer();

			virtual void Start();
			virtual double Time() const;

		private:
			unsigned int m_currClock;
		};
	}
}

#endif

#endif
