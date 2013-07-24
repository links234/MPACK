#include "EventLoop.hpp"

#include "Platform.hpp"

#include "AndroidEventLoop.hpp"
#include "WindowsEventLoop.hpp"

namespace Core
{
	EventLoop::EventLoop()
		: m_pActivityHandler(NULL)
	{
	}

	EventLoop::~EventLoop()
	{
	}

	EventLoop* EventLoop::Initialize(void *data)
	{
		EventLoop *pEventLoop=NULL;
#ifdef ANDROID_PLATFORM
		pEventLoop=(EventLoop*)new AndroidEventLoop(data);
#elif	defined(WINDOWS_PLATFORM)
		pEventLoop=(EventLoop*)new WindowsEventLoop(data);
#endif
		return pEventLoop;
	}
}
