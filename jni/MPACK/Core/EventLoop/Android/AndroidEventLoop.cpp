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
			mEnabled(false), mQuit(false), mDisplay(EGL_NO_DISPLAY), mSurface(EGL_NO_CONTEXT),
			mContext(EGL_NO_SURFACE)
		{
			Global::pAndroidApp->userData = this;
			Global::pAndroidApp->onAppCmd = callback_event;
			Global::pAndroidApp->onInputEvent = callback_input;
		}

		ReturnValue AndroidEventLoop::Run(ActivityHandler* pActivityHandler)
		{
			int32_t lResult;
			int32_t lEvents;
			android_poll_source* lSource;

			// Makes sure native glue is not stripped by the linker.
			app_dummy();
			m_pActivityHandler = pActivityHandler;

			// Global step loop.
			LOGI("Starting event loop");
			while (true)
			{
				Global::pContext->pTimeService->Update();
				Global::pContext->pInputService->Update();
				LOGD("AndroidEventLoop::1");
				// Event processing loop.
				while ((lResult = ALooper_pollAll(mEnabled ? 0 : -1, NULL, &lEvents, (void**) &lSource)) >= 0)
				{
					// An event has to be processed.
					if (lSource != NULL)
					{
						LOGI("Processing an event");
						lSource->process(Global::pAndroidApp, lSource);
					}
					// Application is getting destroyed.
					if (Global::pAndroidApp->destroyRequested)
					{
						LOGI("Exiting event loop");
						return RETURN_VALUE_OK;
					}
				}
				LOGD("AndroidEventLoop::2");
				// Steps the application.
				if ((mEnabled) && (!mQuit))
				{
					LOGD("AndroidEventLoop::2.1");
					if (m_pActivityHandler->onStep() != RETURN_VALUE_OK)
					{
						mQuit = true;
						ANativeActivity_finish(Global::pAndroidApp->activity);
					}
					LOGD("AndroidEventLoop::2.2");
					if(eglSwapBuffers(mDisplay, mSurface)!=EGL_TRUE)
					{
						LOGE("Error %d swapping buffers.",eglGetError());
						mQuit = true;
						ANativeActivity_finish(Global::pAndroidApp->activity);
					}
					LOGD("AndroidEventLoop::2.3");
				}
				LOGD("AndroidEventLoop::3");
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
			if ((!mEnabled) && (Global::pAndroidApp->window != NULL))
			{
				mQuit = false; mEnabled = true;
				if ( InitializeDisplay() != RETURN_VALUE_OK )
				{
					mQuit = true;
					Deactivate();
					ANativeActivity_finish(Global::pAndroidApp->activity);
					return;
				}
				if (m_pActivityHandler->onActivate() != RETURN_VALUE_OK)
				{
					mQuit = true;
					Deactivate();
					ANativeActivity_finish(Global::pAndroidApp->activity);
				}
			}
		}

		void AndroidEventLoop::Deactivate()
		{
			if (mEnabled)
			{
				m_pActivityHandler->onDeactivate();
				mEnabled = false;
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
					LOGD("OK HERE! 0");
					Activate();
					LOGD("OK HERE! 1");
					m_pActivityHandler->onGainFocus();
					LOGD("OK HERE! 2");
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
			AndroidEventLoop& lEventLoop = *(AndroidEventLoop*) pApplication->userData;
			lEventLoop.ProcessAppEvent(pCommand);
		}

		int32_t AndroidEventLoop::ProcessInputEvent(AInputEvent* pEvent)
		{
			int32_t lEventType = AInputEvent_getType(pEvent);
			switch (lEventType)
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
			AndroidEventLoop& lEventLoop = *(AndroidEventLoop*) pApplication->userData;
			return lEventLoop.ProcessInputEvent(pEvent);
		}

		ReturnValue AndroidEventLoop::InitializeDisplay()
		{
			int mWidth, mHeight;

			EGLint lFormat, lNumConfigs, lErrorResult;
			EGLConfig lConfig;

			const EGLint lAttributes[] =
				{
					EGL_RENDERABLE_TYPE, EGL_WINDOW_BIT,
					EGL_RED_SIZE, 8,
					EGL_GREEN_SIZE, 8,
					EGL_BLUE_SIZE, 8,
					EGL_DEPTH_SIZE, 24,
					EGL_NONE
				};
			const EGLint lContextAttrib[] =
			{
				EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
			};

			// Retrieves a display connection and initializes it.
			mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			if (mDisplay == EGL_NO_DISPLAY)
			{
				LOGE("EGL_NO_DISPLAY");
				goto ERROR;
			}
			if (!eglInitialize(mDisplay, NULL, NULL))
			{
				LOGE("Unable to initialize display");
				goto ERROR;
			}

			// Selects the first OpenGL configuration found.
			if(!eglChooseConfig(mDisplay, lAttributes, &lConfig, 1, &lNumConfigs) || (lNumConfigs <= 0))
			{
				LOGE("Unable to select display configuration");
				goto ERROR;
			}

			// Reconfigures the Android window with the EGL format.
			if (!eglGetConfigAttrib(mDisplay, lConfig, EGL_NATIVE_VISUAL_ID, &lFormat))
			{
				LOGE("Unable to configure window format");
				goto ERROR;
			}
			ANativeWindow_setBuffersGeometry(Global::pAndroidApp->window, 0, 0, lFormat);
			// Creates the display surface.
			mSurface = eglCreateWindowSurface(mDisplay, lConfig, Global::pAndroidApp->window, NULL);
			if (mSurface == EGL_NO_SURFACE)
			{
				LOGE("EGL_NO_SURFACE");
				goto ERROR;
			}
			mContext = eglCreateContext(mDisplay, lConfig, EGL_NO_CONTEXT, lContextAttrib);
			if (mContext == EGL_NO_CONTEXT)
			{
				LOGE("EGL_NO_CONTEXT");
				goto ERROR;
			}

			// Activates the display surface.
			LOGD("Activating the display.");
			if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)
			 || !eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &mWidth)
			 || !eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &mHeight)
			 || (mWidth <= 0) || (mHeight <= 0))
			{
				LOGE("Unable to activate display");
				goto ERROR;
			}

			// Displays information about OpenGL.
			LOGI("Starting GraphicsService");
			LOGI("Version  : %s", glGetString(GL_VERSION));
			LOGI("Vendor   : %s", glGetString(GL_VENDOR));
			LOGI("Renderer : %s", glGetString(GL_RENDERER));
			LOGI("Viewport : %d x %d", mWidth, mHeight);

			Graphics::Render::SetScreenSize(mWidth,mHeight);

			return RETURN_VALUE_OK;

		ERROR:
			LOGE("Error while starting GraphicsService");
			DestroyDisplay();
			return RETURN_VALUE_KO;
		}

		void AndroidEventLoop::DestroyDisplay()
		{
			if (mDisplay != EGL_NO_DISPLAY)
			{
				eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
				if (mContext != EGL_NO_CONTEXT)
				{
					eglDestroyContext(mDisplay, mContext);
					mContext = EGL_NO_CONTEXT;
				}
				if (mSurface != EGL_NO_SURFACE)
				{
					eglDestroySurface(mDisplay, mSurface);
					mSurface = EGL_NO_SURFACE;
				}
				eglTerminate(mDisplay);
				mDisplay = EGL_NO_DISPLAY;
			}
		}
	}
}

#endif

