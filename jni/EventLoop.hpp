#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include "ActivityHandler.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>

namespace Core
{
    class EventLoop
    {
    public:
        EventLoop();
        void Run(ActivityHandler* pActivityHandler);

    protected:
        void Activate();
        void Deactivate();

        void ProcessAppEvent(int32_t pCommand);
        int32_t ProcessInputEvent(AInputEvent* pEvent);
        void ProcessSensorEvent();

    private:
        // Private callbacks handling events occuring in the thread loop.
        static void callback_event(android_app* pApplication, int32_t pCommand);
        static int32_t callback_input(android_app* pApplication, AInputEvent* pEvent);

    private:
        // Saves application state when application is active/paused.
        bool mEnabled;
        // Indicates if the event handler wants to exit.
        bool mQuit;
        // Activity event observer.
        ActivityHandler* mActivityHandler;
    };
}
#endif
