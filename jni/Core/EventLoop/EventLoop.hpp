#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include "Types.hpp"

namespace Core
{
	class ActivityHandler;
}

namespace Core
{
    class EventLoop
    {
    public:
    	EventLoop();
    	virtual ~EventLoop();

        virtual Status Run(ActivityHandler *pActivityHandler)=0;

        static EventLoop* Initialize(void *data);

    protected:
        ActivityHandler *m_pActivityHandler;
    };
}
#endif
