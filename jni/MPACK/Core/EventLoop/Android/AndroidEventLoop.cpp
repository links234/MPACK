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
			m_enabled(false), m_quit(false), m_paused(false), m_width(0), m_height(0)
		{
			Global::pAndroidApp->userData = this;
			Global::pAndroidApp->onAppCmd = callback_event;
			Global::pAndroidApp->onInputEvent = callback_input;
		}

		ReturnValue AndroidEventLoop::Run(Application* pApplication)
		{
			int32_t result;
			int32_t events;
			android_poll_source* source;

			// Makes sure native glue is not stripped by the linker.
			app_dummy();
			m_pApplication = pApplication;

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

				//LOGD("m_enabled = %d",m_enabled);
				//LOGD("m_quit = %d", m_quit);
				//LOGD("context bound? = %d", m_window.IsContextBound());

				// Steps the application.
				if ((m_enabled) && (!m_quit) && (m_window.IsContextBound()))
				{
					//LOGD("TESTING");
					if (m_pApplication->onStep() != RETURN_VALUE_OK)
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
			LOGD("AndroidEventLoop::Activate()");

			if ((!m_enabled) && (Global::pAndroidApp->window != NULL))
			{
				bool haveToReload = false;

				m_quit = false;
				m_enabled = true;

				LOGD("CONTEXT BOUND = %d",m_window.IsContextBound());

				if (!m_window.IsContextBound())
				{
					LOGD("CONTEXT NOT BOUND");
					if (!m_window.IsSurfaceCreated())
					{
						LOGD("SURFACE NOT CREATED");
						if (!m_window.IsContextCreated())
						{
							LOGD("CONTEXT NOT CREATED");
							EGLBufferConfigManager *pConfigManager = NULL;
							EGLint format;
							EGLint redSize=0, greenSize=0, blueSize=0, depthSize=16;

							if(m_window.Init() != RETURN_VALUE_OK)
							{
								goto ERROR;
							}

							pConfigManager = new EGLBufferConfigManager(&m_window);
							LOGI("AndroidEventLoop::InitializeDisplay() info: number of configurations = %d",pConfigManager->GetCount());
							pConfigManager->PrintAll();
							pConfigManager->Match(redSize,greenSize,blueSize,depthSize);
							delete pConfigManager;

							LOGI("AndroidEventLoop::InitializeDisplay() info: matched configuration to: (R:%d G:%d B:%d depth:%d)",redSize,greenSize,blueSize,depthSize);

							if(m_window.ChooseConfig(redSize,greenSize,blueSize,depthSize) != RETURN_VALUE_OK)
							{
								goto ERROR;
							}

							if(m_window.GetFormat(format) != RETURN_VALUE_OK)
							{
								goto ERROR;
							}
							ANativeWindow_setBuffersGeometry(Global::pAndroidApp->window, 0, 0, format);

							if(m_window.CreateContext() != RETURN_VALUE_OK)
							{
								goto ERROR;
							}

							haveToReload = true;
						}

						if(m_window.CreateSurface(Global::pAndroidApp->window) != RETURN_VALUE_OK)
						{
							goto ERROR;
						}
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
				}

				// Displays information about OpenGL.
				LOGI("Starting GraphicsService");
				LOGI("Version  : %s", glGetString(GL_VERSION));
				LOGI("Vendor   : %s", glGetString(GL_VENDOR));
				LOGI("Renderer : %s", glGetString(GL_RENDERER));
				LOGI("Viewport : %d x %d", m_width, m_height);

				Graphics::Render::SetScreenSize(m_width,m_height);

				Global::pContext->pInputService->Update();
				Global::pContext->pInputService->Update();

				if(haveToReload)
				{
					if (m_pApplication->onActivate() != RETURN_VALUE_OK)
					{
						m_quit = true;
						Deactivate();
						ANativeActivity_finish(Global::pAndroidApp->activity);
					}
				}

				//return RETURN_VALUE_OK;
			}

			return;
		ERROR:
			m_enabled = false;
			m_quit = true;
			Deactivate();
			ANativeActivity_finish(Global::pAndroidApp->activity);
		}

		void AndroidEventLoop::Deactivate()
		{
			LOGD("AndroidEventLoop::Deactivate()");

			if (m_enabled)
			{
				m_pApplication->onDeactivate();
				m_enabled = false;
			}

			m_width=0;
			m_height=0;
			m_window.Destroy();
		}

		void AndroidEventLoop::ProcessAppEvent(int32_t pCommand)
		{
			switch (pCommand)
			{
				case APP_CMD_CONFIG_CHANGED:
					LOGD("APP_CMD_CONFIG_CHANGED");
					Activate();
					m_pApplication->onConfigurationChanged();
					break;
				case APP_CMD_INIT_WINDOW:
					LOGD("APP_CMD_INIT_WINDOW");
					Activate();
					break;
				case APP_CMD_DESTROY:
					LOGD("APP_CMD_DESTROY");
					m_pApplication->onDestroy();
					m_window.InvalidateSurface();
					m_window.InvalidateContext();
					m_enabled = false;
					break;
				case APP_CMD_GAINED_FOCUS:
					LOGD("APP_CMD_GAINED_FOCUS");
					m_pApplication->onGainFocus();
					break;
				case APP_CMD_LOST_FOCUS:
					LOGD("APP_CMD_LOST_FOCUS");
					m_pApplication->onLostFocus();
					break;
				case APP_CMD_LOW_MEMORY:
					LOGD("APP_CMD_LOW_MEMORY");
					m_pApplication->onLowMemory();
					break;
				case APP_CMD_PAUSE:
					LOGD("APP_CMD_PAUSE");
					m_pApplication->onPause();
					m_enabled = false;
					//m_window.InvalidateSurface();
					break;
				case APP_CMD_RESUME:
					LOGD("APP_CMD_RESUME");
					Activate();
					m_pApplication->onResume();
					break;
				case APP_CMD_SAVE_STATE:
					LOGD("APP_CMD_SAVE_STATE");
					m_pApplication->onSaveState(&Global::pAndroidApp->savedState,
						&Global::pAndroidApp->savedStateSize);
					break;
				case APP_CMD_START:
					LOGD("APP_CMD_START");
					Activate();
					m_pApplication->onStart();
					break;
				case APP_CMD_STOP:
					LOGD("APP_CMD_STOP");
					m_pApplication->onStop();
					m_window.InvalidateSurface();
					m_enabled = false;
					break;
				case APP_CMD_TERM_WINDOW:
					LOGD("APP_CMD_TERM_WINDOW");
					m_window.InvalidateSurface();
					m_enabled = false;
					break;
				default:
					break;
			}

			LOGD("m_enabled = %d",m_enabled);
			LOGD("is context bound? = %d",m_window.IsContextBound());
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
		}
	}
}

#endif
