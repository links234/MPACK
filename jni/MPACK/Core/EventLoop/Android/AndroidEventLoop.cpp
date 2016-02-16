#ifdef ANDROID_PLATFORM

#include "AndroidEventLoop.hpp"

#include "Application.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "EGLBufferConfigManager.hpp"
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
			m_width(0), m_height(0), m_requestExit(false)
		{
			m_state = APP_STATUS_RUNNING;

			Global::pAndroidApp->userData = this;
			Global::pAndroidApp->onAppCmd = callback_event;
			Global::pAndroidApp->onInputEvent = callback_input;
		}

		ReturnValue AndroidEventLoop::Run(Application* pApplication)
		{
			// Global step loop.
			LOGI("Starting event loop");

			int32_t result;
			int32_t events;
			android_poll_source* source;

			// Makes sure native glue is not stripped by the linker.
			app_dummy();
			m_pApplication = pApplication;

			bool hasInitializedGL = false;

			EGLBufferConfigManager *pConfigManager = NULL;
			EGLint format;
			EGLint redSize=0, greenSize=0, blueSize=0, depthSize=16;

			if(m_egl.Init() != RETURN_VALUE_OK)
			{
				LOGE("Failed to initialize EGL!");
				return RETURN_VALUE_KO;
			}

			pConfigManager = new EGLBufferConfigManager(&m_egl);
			LOGI("AndroidEventLoop::InitializeDisplay() info: number of configurations = %d",pConfigManager->GetCount());
			pConfigManager->PrintAll();
			pConfigManager->Match(redSize,greenSize,blueSize,depthSize);
			delete pConfigManager;

			if(m_egl.ChooseConfig(redSize,greenSize,blueSize,depthSize) != RETURN_VALUE_OK)
			{
				LOGE("Failed to choose EGL configuration!");
				return RETURN_VALUE_KO;
			}

			while (IsAppRunning())
			{
				while ((result = ALooper_pollAll(IsAppRunning(), NULL, &events, (void**) &source)) >= 0)
				{
					if (source != NULL)
					{
						source->process(Global::pAndroidApp, source);
					}
				}

				Global::pContext->pTimeService->Update();
				Global::pContext->pInputService->Update();

				if (IsContextLost())
				{
					if (hasInitializedGL)
					{
						hasInitializedGL = false;
						m_pApplication->onDeactivate();
					}
				}

				if (ShouldRender())
				{
					if (!hasInitializedGL)
					{
						m_width = m_egl.GetSurfaceWidth();
						m_height = m_egl.GetSurfaceHeight();
						Graphics::Render::SetScreenSize(m_width,m_height);
						m_pApplication->onActivate();
						hasInitializedGL = true;
					}

					if (!IsExiting())
					{
						if (m_pApplication->onStep() != RETURN_VALUE_OK)
						{
							RequestExit();
						}

						m_egl.SwapBuffers();
					}
				}
			}

			if(m_requestExit)
			{
				m_state |= APP_STATUS_RUNNING;
			}

			if (hasInitializedGL)
			{
				hasInitializedGL = false;
				m_pApplication->onDeactivate();
			}
			return RETURN_VALUE_OK;
		}

		void* AndroidEventLoop::GetWindowHandle() const
		{
			return NULL;
		}

		void AndroidEventLoop::ProcessAppEvent(int32_t pCommand)
		{
			switch (pCommand)
			{
				case APP_CMD_CONFIG_CHANGED:
					LOGD("APP_CMD_CONFIG_CHANGED");
					m_pApplication->onConfigurationChanged();
					break;
				case APP_CMD_DESTROY:
					LOGD("APP_CMD_DESTROY");
					m_state &= ~APP_STATUS_RUNNING;
					break;
				case APP_CMD_INIT_WINDOW:
					LOGD("APP_CMD_INIT_WINDOW");
					m_state |= APP_STATUS_HAS_REAL_SURFACE;
					m_egl.SetWindow(Global::pAndroidApp->window);
					break;
				case APP_CMD_TERM_WINDOW:
					LOGD("APP_CMD_TERM_WINDOW");
					m_state &= ~APP_STATUS_HAS_REAL_SURFACE;
					m_egl.SetWindow(NULL);
					break;
				case APP_CMD_GAINED_FOCUS:
					LOGD("APP_CMD_GAINED_FOCUS");
					m_state |= APP_STATUS_FOCUSED;

					m_pApplication->onGainFocus();
					break;
				case APP_CMD_LOST_FOCUS:
					LOGD("APP_CMD_LOST_FOCUS");
					m_state &= ~APP_STATUS_FOCUSED;

					m_pApplication->onLostFocus();
					break;
				case APP_CMD_PAUSE:
					LOGD("APP_CMD_PAUSE");
					m_state &= ~APP_STATUS_ACTIVE;

					m_pApplication->onPause();
					break;
				case APP_CMD_RESUME:
					LOGD("APP_CMD_RESUME");
					m_state |= APP_STATUS_ACTIVE;

					m_pApplication->onResume();
					break;
				case APP_CMD_START:
					LOGD("APP_CMD_START");
					m_pApplication->onStart();
					break;
				case APP_CMD_STOP:
					LOGD("APP_CMD_STOP");
					m_pApplication->onStop();
					break;
				case APP_CMD_LOW_MEMORY:
					LOGD("APP_CMD_LOW_MEMORY");
					m_pApplication->onLowMemory();
					break;
				case APP_CMD_SAVE_STATE:
					LOGD("APP_CMD_SAVE_STATE");
					m_pApplication->onSaveState(&Global::pAndroidApp->savedState,
						&Global::pAndroidApp->savedStateSize);
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

		bool AndroidEventLoop::ShouldRender()
		{
		    if (IsAppInteractable())
		    {
		        if (!m_egl.IsReadyToRender(true))
		        {
		            return false;
		        }
		        return true;
		    }
		    else
		    {
		        if (m_egl.IsReadyToRender(false))
		        {
		            return true;
		        }
		    }
		    return false;
		}

		bool AndroidEventLoop::IsAppInteractable()
		{
			return ((m_state & APP_STATUS_INTERACTABLE) == APP_STATUS_INTERACTABLE) ? true : false;
		}

		bool AndroidEventLoop::IsContextLost()
		{
		    return !m_egl.HasContext();
		}

		bool AndroidEventLoop::IsContextBound()
		{
		    return m_egl.IsBound();
		}

		bool AndroidEventLoop::IsAppRunning()
		{
		    return (m_state & APP_STATUS_RUNNING) ? true : false;
		}

		bool AndroidEventLoop::IsExiting()
		{
			return m_requestExit;
		}

		void AndroidEventLoop::RequestExit()
		{
			m_requestExit = true;
			ANativeActivity_finish(Global::pAndroidApp->activity);
		}
	}
}

#endif
