#ifdef ANDROID_PLATFORM

#ifndef MPACK_ANDROIDTIMESERVICE_HPP
#define MPACK_ANDROIDTIMESERVICE_HPP

#include "TimeService.hpp"

namespace MPACK
{
	namespace Time
	{
		class AndroidTimeService : public TimeService
		{
		public:
			AndroidTimeService();

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
