#include "EventLoop.hpp"

#include "AndroidEventLoop.hpp"
#include "WindowsEventLoop.hpp"
#include "LinuxEventLoop.hpp"

namespace MPACK
{
	namespace Core
	{
		EventLoop::EventLoop()
			: m_pApplication(NULL)
		{
		}

		EventLoop::~EventLoop()
		{
		}

		void EventLoop::ShowCursor()
		{
		}

		void EventLoop::HideCursor()
		{
		}

		EventLoop* EventLoop::Initialize(void *data)
		{
			EventLoop *pEventLoop=NULL;
	#ifdef ANDROID_PLATFORM
			pEventLoop=(EventLoop*)new AndroidEventLoop(data);
	#elif	defined(WINDOWS_PLATFORM)
			pEventLoop=(EventLoop*)new WindowsEventLoop(data);
	#elif	defined(LINUX_PLATFORM)
			pEventLoop=(EventLoop*)new LinuxEventLoop(data);
	#endif
			return pEventLoop;
		}
	}
}
