#ifndef MPACK_EVENTLOOP_HPP
#define MPACK_EVENTLOOP_HPP

#include "Types.hpp"

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
		class EventLoop
		{
		public:
			EventLoop();
			virtual ~EventLoop();

			virtual ReturnValue Run(Application *pApplication)=0;

			virtual void ShowCursor();
			virtual void HideCursor();

			virtual void* GetWindowHandle() const = 0;

			static EventLoop* Initialize(void *data);

		protected:
			Application *m_pApplication;
		};
	}
}
#endif
