#ifndef MPACK_EVENTLOOP_HPP
#define MPACK_EVENTLOOP_HPP

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

        virtual ReturnValue Run(ActivityHandler *pActivityHandler)=0;

        virtual void ShowCursor();
        virtual void HideCursor();

        virtual void* GetWindowHandle() const = 0;

        static EventLoop* Initialize(void *data);

    protected:
        ActivityHandler *m_pActivityHandler;
    };
}
#endif
