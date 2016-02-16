#ifdef OSX_PLATFORM

#ifndef MPACK_OSXEVENTLOOP_HPP
#define MPACK_OSXEVENTLOOP_HPP

#include "Types.hpp"
#include "EventLoop.hpp"

namespace MPACK
{
	namespace Core
	{
		class Application;
	}
}

namespace MPACK
{
	namespace Core
	{
		class OSXEventLoop : public EventLoop
		{
		public:
			OSXEventLoop(void *data);
			ReturnValue Run(Application* pApplication);

			void ShowCursor();
			void HideCursor();

			void* GetWindowHandle() const;

		protected:
		};
	}
}
#endif

#endif
