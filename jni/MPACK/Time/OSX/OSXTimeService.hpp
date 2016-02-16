#ifdef OSX_PLATFORM

#ifndef MPACK_OSXTIMESERVICE_HPP
#define MPACK_OSXTIMESERVICE_HPP

#include "TimeService.hpp"

namespace MPACK
{
	namespace Time
	{
		class OSXTimeService : public TimeService
		{
		public:
			OSXTimeService();

			void Reset();
			void Update();

			double Now();
			float 	Elapsed();

		private:
			float mElapsed;
			double mLastTime;
		};
	}
}

#endif

#endif
