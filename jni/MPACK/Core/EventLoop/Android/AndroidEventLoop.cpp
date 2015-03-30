#ifdef ANDROID_PLATFORM

#include "AndroidEventLoop.hpp"

#include "ActivityHandler.hpp"
#include "Context.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "Global.hpp"
#include "Render.hpp"
#include "Log.hpp"

namespace MPACK
{
	namespace Core
	{
		AndroidEventLoop::AndroidEventLoop(void *data) :
			m_enabled(false), m_quit(false), m_display(EGL_NO_DISPLAY), m_surface(EGL_NO_CONTEXT),
			m_context(EGL_NO_SURFACE), m_majorVersion(0), m_minorVersion(0)
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
					if(eglSwapBuffers(m_display, m_surface)!=EGL_TRUE)
					{
						LOGE("Error %d swapping buffers.",eglGetError());
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
			int width, height;

			EGLint format, numConfigs, errorResult;
			EGLConfig config;
			EGLint result;

			const EGLint attributes[] =
				{
					EGL_RENDERABLE_TYPE, EGL_WINDOW_BIT,
					EGL_RED_SIZE, 8,
					EGL_GREEN_SIZE, 8,
					EGL_BLUE_SIZE, 8,
					EGL_DEPTH_SIZE, 16,
					EGL_NONE
				};
			const EGLint contextAttrib[] =
			{
				EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
			};

			// Retrieves a display connection and initializes it.
			EGL_CHECK( m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY) );
			if (m_display == EGL_NO_DISPLAY)
			{
				LOGE("EGL_NO_DISPLAY");
				goto ERROR;
			}
			EGL_CHECK( result = eglInitialize(m_display, &m_majorVersion, &m_minorVersion) );
			if (!result)
			{
				LOGE("Unable to initialize display");
				goto ERROR;
			}

			// Selects the first OpenGL configuration found.
			EGL_CHECK( result = eglChooseConfig(m_display, attributes, &config, 1, &numConfigs) );
			if(!result || (numConfigs <= 0))
			{
				Debug::EGL::Assert("Unable to select display configuration");
				goto ERROR;
			}

			// Reconfigures the Android window with the EGL format.
			EGL_CHECK( result = eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format) );
			if (!result)
			{
				LOGE("Unable to configure window format");
				goto ERROR;
			}
			ANativeWindow_setBuffersGeometry(Global::pAndroidApp->window, 0, 0, format);

			// Creates the display surface.
			EGL_CHECK( m_surface = eglCreateWindowSurface(m_display, config, Global::pAndroidApp->window, NULL) );
			if (m_surface == EGL_NO_SURFACE)
			{
				LOGE("EGL_NO_SURFACE");
				goto ERROR;
			}
			EGL_CHECK( m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttrib) );
			if (m_context == EGL_NO_CONTEXT)
			{
				LOGE("EGL_NO_CONTEXT");
				goto ERROR;
			}

			// Activates the display surface.
			LOGD("Activating the display.");
			EGL_CHECK( result = eglMakeCurrent(m_display, m_surface, m_surface, m_context) );
			EGL_CHECK( result += eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width) );
			EGL_CHECK( result += eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height) );
			if (!result || (width <= 0) || (height <= 0))
			{
				LOGE("Unable to activate display");
				goto ERROR;
			}

			// Displays information about OpenGL.
			LOGI("Starting GraphicsService");
			LOGI("Version  : %s", glGetString(GL_VERSION));
			LOGI("Vendor   : %s", glGetString(GL_VENDOR));
			LOGI("Renderer : %s", glGetString(GL_RENDERER));
			LOGI("Viewport : %d x %d", width, height);

			Graphics::Render::SetScreenSize(width,height);

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("Error while starting GraphicsService");
			DestroyDisplay();
			return RETURN_VALUE_KO;
		}

		void AndroidEventLoop::DestroyDisplay()
		{
			if (m_display != EGL_NO_DISPLAY)
			{
				EGL_CHECK( eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) );
				if (m_context != EGL_NO_CONTEXT)
				{
					EGL_CHECK( eglDestroyContext(m_display, m_context) );
					m_context = EGL_NO_CONTEXT;
				}
				if (m_surface != EGL_NO_SURFACE)
				{
					EGL_CHECK( eglDestroySurface(m_display, m_surface) );
					m_surface = EGL_NO_SURFACE;
				}
				EGL_CHECK( eglTerminate(m_display) );
				m_display = EGL_NO_DISPLAY;
			}
		}
	}
}

#endif

