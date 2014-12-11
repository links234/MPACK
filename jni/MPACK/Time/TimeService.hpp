#ifndef MPACK_TIMESERVICE_HPP
#define MPACK_TIMESERVICE_HPP

namespace MPACK
{
	namespace Time
	{
		class TimeService
		{
		public:
			TimeService();
			virtual ~TimeService();

			virtual void Reset() = 0;
			virtual void Update() = 0;

			virtual double 	Now() = 0;
			virtual float		Elapsed() = 0;

			static TimeService* Initialize();
		};
	}
}
#endif
