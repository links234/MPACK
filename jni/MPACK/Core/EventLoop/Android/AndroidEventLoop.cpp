#ifdef ANDROID_PLATFORM

#include "AndroidEventLoop.hpp"

#include "ActivityHandler.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "EGLWindow.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "Render.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Core
	{
		AndroidEventLoop::AndroidEventLoop(void *data) :
			m_enabled(false), m_quit(false), m_width(0), m_height(0)
		{
			Global::pAndroidApp->userData = this;
			Global::pAndroidApp->onAppCmd = callback_event;
			Global::pAndroidApp->onInputEvent = callback_input;
		}

		ReturnValue AndroidEventLoop::Run(ActivityHandler* pActivityHandler)
		{
			int32_t result;
			int32_t events;
			android_poll_source* source;

			// Makes sure native glue is not stripped by the linker.
			app_dummy();
			m_pActivityHandler = pActivityHandler;

			// Global step loop.
			LOGI("Starting event loop");
			while (true)
			{
				Global::pContext->pTimeService->Update();
				Global::pContext->pInputService->Update();

				// Event processing loop.
				while ((result = ALooper_pollAll(m_enabled ? 0 : -1, NULL, &events, (void**) &source)) >= 0)
				{
					// An event has to be processed.
					if (source != NULL)
					{
						source->process(Global::pAndroidApp, source);
					}
					// Application is getting destroyed.
					if (Global::pAndroidApp->destroyRequested)
					{
						LOGI("Exiting event loop");
						return RETURN_VALUE_OK;
					}
				}

				// Steps the application.
				if ((m_enabled) && (!m_quit))
				{
					if (m_pActivityHandler->onStep() != RETURN_VALUE_OK)
					{
						m_quit = true;
						ANativeActivity_finish(Global::pAndroidApp->activity);
					}
					if(m_window.SwapBuffers() != RETURN_VALUE_OK)
					{
						m_quit = true;
						ANativeActivity_finish(Global::pAndroidApp->activity);
					}
				}
			}
			return RETURN_VALUE_OK;
		}

		void* AndroidEventLoop::GetWindowHandle() const
		{
			return NULL;
		}

		void AndroidEventLoop::Activate()
		{
			// Enables activity only if a window is available.
			if ((!m_enabled) && (Global::pAndroidApp->window != NULL))
			{
				m_quit = false;
				m_enabled = true;
				if ( InitializeDisplay() != RETURN_VALUE_OK )
				{
					m_quit = true;
					Deactivate();
					ANativeActivity_finish(Global::pAndroidApp->activity);
					return;
				}
				if (m_pActivityHandler->onActivate() != RETURN_VALUE_OK)
				{
					m_quit = true;
					Deactivate();
					ANativeActivity_finish(Global::pAndroidApp->activity);
				}
			}
		}

		void AndroidEventLoop::Deactivate()
		{
			if (m_enabled)
			{
				m_pActivityHandler->onDeactivate();
				m_enabled = false;
			}
			DestroyDisplay();
		}

		void AndroidEventLoop::ProcessAppEvent(int32_t pCommand)
		{
			switch (pCommand)
			{
				case APP_CMD_CONFIG_CHANGED:
					m_pActivityHandler->onConfigurationChanged();
					break;
				case APP_CMD_INIT_WINDOW:
					m_pActivityHandler->onCreateWindow();
					break;
				case APP_CMD_DESTROY:
					m_pActivityHandler->onDestroy();
					break;
				case APP_CMD_GAINED_FOCUS:
					Activate();
					m_pActivityHandler->onGainFocus();
					break;
				case APP_CMD_LOST_FOCUS:
					m_pActivityHandler->onLostFocus();
					Deactivate();
					break;
				case APP_CMD_LOW_MEMORY:
					m_pActivityHandler->onLowMemory();
					break;
				case APP_CMD_PAUSE:
					m_pActivityHandler->onPause();
					Deactivate();
					break;
				case APP_CMD_RESUME:
					m_pActivityHandler->onResume();
					break;
				case APP_CMD_SAVE_STATE:
					m_pActivityHandler->onSaveState(&Global::pAndroidApp->savedState,
						&Global::pAndroidApp->savedStateSize);
					break;
				case APP_CMD_START:
					m_pActivityHandler->onStart();
					break;
				case APP_CMD_STOP:
					m_pActivityHandler->onStop();
					break;
				case APP_CMD_TERM_WINDOW:
					m_pActivityHandler->onDestroyWindow();
					Deactivate();
					break;
				default:
					break;
			}
		}

		void AndroidEventLoop::callback_event(android_app* pApplication, int32_t pCommand)
		{
			AndroidEventLoop& eventLoop = *(AndroidEventLoop*) pApplication->userData;
			eventLoop.ProcessAppEvent(pCommand);
		}

		int32_t AndroidEventLoop::ProcessInputEvent(AInputEvent* pEvent)
		{
			int32_t eventType = AInputEvent_getType(pEvent);
			switch (eventType)
			{
				case AINPUT_EVENT_TYPE_MOTION:
					switch (AInputEvent_getSource(pEvent))
					{
						case AINPUT_SOURCE_TOUCHSCREEN:
							return Global::pContext->pInputService->onTouchEvent(pEvent);
						break;
					}
				break;
				case AINPUT_EVENT_TYPE_KEY:
					switch (AKeyEvent_getKeyCode(pEvent))
					{
						case AKEYCODE_BACK:
							return Global::pContext->pInputService->onKeyBack();
						break;
					}
				break;
			}
			return 0;
		}

		int32_t AndroidEventLoop::callback_input(android_app* pApplication, AInputEvent* pEvent)
		{
			AndroidEventLoop& eventLoop = *(AndroidEventLoop*) pApplication->userData;
			return eventLoop.ProcessInputEvent(pEvent);
		}

		ReturnValue AndroidEventLoop::InitializeDisplay()
		{
			EGLint format;

			if(m_window.Init() != RETURN_VALUE_OK)
			{
				goto ERROR;
			}

			if(m_window.ChooseConfig() != RETURN_VALUE_OK)
			{
				goto ERROR;
			}

			if(m_window.GetFormat(format) != RETURN_VALUE_OK)
			{
				goto ERROR;
			}
			ANativeWindow_setBuffersGeometry(Global::pAndroidApp->window, 0, 0, format);

			if(m_window.CreateSurface(Global::pAndroidApp->window) != RETURN_VALUE_OK)
			{
				goto ERROR;
			}

			if(m_window.Bind(m_width, m_height) != RETURN_VALUE_OK)
			{
				goto ERROR;
			}

			if(m_width<=0 || m_height<=0)
			{
				LOGE("AndroidEventLoop::InitializeDisplay() invalid width or height (%d x %d)", m_width, m_height);
				goto ERROR;
			}

			// Displays information about OpenGL.
			LOGI("Starting GraphicsService");
			LOGI("Version  : %s", glGetString(GL_VERSION));
			LOGI("Vendor   : %s", glGetString(GL_VENDOR));
			LOGI("Renderer : %s", glGetString(GL_RENDERER));
			LOGI("Viewport : %d x %d", m_width, m_height);

			Graphics::Render::SetScreenSize(m_width,m_height);

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("AndroidEventLoop::InitializeDisplay() failed");
			DestroyDisplay();
			return RETURN_VALUE_KO;
		}

		void AndroidEventLoop::DestroyDisplay()
		{
			m_width=0;
			m_height=0;
			m_window.Destroy();
		}
	}
}

#endif

