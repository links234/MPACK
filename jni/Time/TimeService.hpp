#ifndef TIMESERVICE_HPP
#define TIMESERVICE_HPP

namespace Core
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
#endif
