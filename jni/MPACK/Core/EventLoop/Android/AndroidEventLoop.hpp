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
		enum
		{
			APP_STATUS_RUNNING          = 0x00000001,
			APP_STATUS_ACTIVE           = 0x00000002,
			APP_STATUS_FOCUSED          = 0x00000004,
			APP_STATUS_HAS_REAL_SURFACE  = 0x00000008,

			APP_STATUS_INTERACTABLE		= 0x0000000F
		};

		class AndroidEventLoop : public EventLoop
		{
		public:
			AndroidEventLoop(void *data);
			ReturnValue Run(Application* pApplication);

			void* GetWindowHandle() const;

		protected:
			void ProcessAppEvent(int32_t pCommand);
			int32_t ProcessInputEvent(AInputEvent* pEvent);
			void ProcessSensorEvent();

		private:
			// Private callbacks handling events occuring in the thread loop.
			static void callback_event(android_app* pApplication, int32_t pCommand);
			static int32_t callback_input(android_app* pApplication, AInputEvent* pEvent);

		private:
			bool ShouldRender();
			bool IsAppInteractable();
			bool IsContextLost();
			bool IsContextBound();
			bool IsAppRunning();
			bool IsExiting();
			void RequestExit();

			bool m_requestExit;

			EGLint		m_width, m_height;
			EGLWindow 	m_egl;

			int m_state;
		};
	}
}
#endif

#endif
