#ifdef OSX_PLATFORM

#include "OSXEventLoop.hpp"

namespace MPACK
{
	namespace Core
	{
		OSXEventLoop::OSXEventLoop(void *data)
		{
		}

		ReturnValue OSXEventLoop::Run(Application* pApplication)
		{
			return RETURN_VALUE_OK;
		}

		void OSXEventLoop::ShowCursor()
		{
		}

		void OSXEventLoop::HideCursor()
		{
		}

		void* OSXEventLoop::GetWindowHandle() const
		{
			return NULL;
		}
	}
}

#endif
