#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXTIMER_HPP
#define MPACK_LINUXTIMER_HPP

#include "Timer.hpp"

namespace MPACK
{
	namespace Time
	{
		class LinuxTimer : public Timer
		{
		public:
			LinuxTimer();
			virtual ~LinuxTimer();

			virtual void Start();
			virtual double Time() const;

		private:
			double	m_lastTime;
		};
	}
}

#endif

#endif
