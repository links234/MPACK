#include "EventLoop.hpp"

#include "InputService.hpp"
#include "Global.hpp"
#include "Log.hpp"

namespace Core
{
    EventLoop::EventLoop() :
        mEnabled(false), mQuit(false),
        mActivityHandler(NULL)
    {
        Global::pAndroidApp->userData = this;
        Global::pAndroidApp->onAppCmd = callback_event;
        Global::pAndroidApp->onInputEvent = callback_input;
    }

    void EventLoop::Run(ActivityHandler* pActivityHandler)
    {
        int32_t lResult;
        int32_t lEvents;
        android_poll_source* lSource;

        // Makes sure native glue is not stripped by the linker.
        app_dummy();
        mActivityHandler = pActivityHandler;

        // Global step loop.
        LOGI("Starting event loop");
        while (true)
        {
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
                    return;
                }
            }

            // Steps the application.
            if ((mEnabled) && (!mQuit))
            {
                if (mActivityHandler->onStep() != STATUS_OK)
                {
                    mQuit = true;
                    ANativeActivity_finish(Global::pAndroidApp->activity);
                }
            }
        }
    }

    void EventLoop::Activate()
    {
        // Enables activity only if a window is available.
        if ((!mEnabled) && (Global::pAndroidApp->window != NULL))
        {
            mQuit = false; mEnabled = true;
            if (mActivityHandler->onActivate() != STATUS_OK)
            {
                mQuit = true;
                Deactivate();
                ANativeActivity_finish(Global::pAndroidApp->activity);
            }
        }
    }

    void EventLoop::Deactivate()
    {
        if (mEnabled)
        {
            mActivityHandler->onDeactivate();
            mEnabled = false;
        }
    }

    void EventLoop::ProcessAppEvent(int32_t pCommand)
    {
        switch (pCommand)
        {
			case APP_CMD_CONFIG_CHANGED:
				mActivityHandler->onConfigurationChanged();
				break;
			case APP_CMD_INIT_WINDOW:
				mActivityHandler->onCreateWindow();
				break;
			case APP_CMD_DESTROY:
				mActivityHandler->onDestroy();
				break;
			case APP_CMD_GAINED_FOCUS:
				Activate();
				mActivityHandler->onGainFocus();
				break;
			case APP_CMD_LOST_FOCUS:
				mActivityHandler->onLostFocus();
				Deactivate();
				break;
			case APP_CMD_LOW_MEMORY:
				mActivityHandler->onLowMemory();
				break;
			case APP_CMD_PAUSE:
				mActivityHandler->onPause();
				Deactivate();
				break;
			case APP_CMD_RESUME:
				mActivityHandler->onResume();
				break;
			case APP_CMD_SAVE_STATE:
				mActivityHandler->onSaveState(&Global::pAndroidApp->savedState,
					&Global::pAndroidApp->savedStateSize);
				break;
			case APP_CMD_START:
				mActivityHandler->onStart();
				break;
			case APP_CMD_STOP:
				mActivityHandler->onStop();
				break;
			case APP_CMD_TERM_WINDOW:
				mActivityHandler->onDestroyWindow();
				Deactivate();
				break;
			default:
				break;
        }
    }

    void EventLoop::callback_event(android_app* pApplication, int32_t pCommand)
    {
        EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
        lEventLoop.ProcessAppEvent(pCommand);
    }

    int32_t EventLoop::ProcessInputEvent(AInputEvent* pEvent)
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

	int32_t EventLoop::callback_input(android_app* pApplication, AInputEvent* pEvent)
	{
		EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
		return lEventLoop.ProcessInputEvent(pEvent);
	}
}
