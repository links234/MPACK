#ifdef ANDROID_PLATFORM

#ifndef MPACK_ANDROIDEVENTLOOP_HPP
#define MPACK_ANDROIDEVENTLOOP_HPP

#include "Types.hpp"
#include "EventLoop.hpp"
#include "EGLWindow.hpp"

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
		class AndroidEventLoop : public EventLoop
		{
		public:
			AndroidEventLoop(void *data);
			ReturnValue Run(Application* pApplication);

			void* GetWindowHandle() const;

		protected:
			void Activate();
			void Deactivate();

			void ProcessAppEvent(int32_t pCommand);
			int32_t ProcessInputEvent(AInputEvent* pEvent);
			void ProcessSensorEvent();

			ReturnValue InitializeDisplay();
			void DestroyDisplay();

		private:
			// Private callbacks handling events occuring in the thread loop.
			static void callback_event(android_app* pApplication, int32_t pCommand);
			static int32_t callback_input(android_app* pApplication, AInputEvent* pEvent);

		private:
			bool m_enabled;
			bool m_quit;
			bool m_paused;

			EGLint		m_width, m_height;
			EGLWindow 	m_window;
		};
	}
}
#endif

#endif
