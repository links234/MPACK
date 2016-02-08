#ifdef OSX_PLATFORM

#ifndef MPACK_OSXTIMER_HPP
#define MPACK_OSXTIMER_HPP

#include "Timer.hpp"

namespace MPACK
{
	namespace Time
	{
		class OSXTimer : public Timer
		{
		public:
			OSXTimer();
			virtual ~OSXTimer();

			virtual void Start();
			virtual double Time() const;

		private:
			double	m_lastTime;
		};
	}
}

#endif

#endif
