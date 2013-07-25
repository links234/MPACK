#ifndef TIMER_HPP
#define TIMER_HPP

namespace Core
{
    class Timer
    {
    public:
    	Timer();
    	virtual ~Timer();

    	virtual void Start() = 0;
    	virtual double Time() const = 0;

    	static Timer* Create();
    };
}
#endif
