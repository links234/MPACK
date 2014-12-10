#ifndef MPACK_ACTIVITYHANDLER_HPP
#define MPACK_ACTIVITYHANDLER_HPP

#include "Types.hpp"

namespace Core
{
    class ActivityHandler
    {
    public:
        virtual ~ActivityHandler() {};

        virtual ReturnValue onActivate() = 0;
        virtual void onDeactivate() = 0;
        virtual ReturnValue onStep() = 0;

        virtual void onStart() {};
        virtual void onResume() {};
        virtual void onPause() {};
        virtual void onStop() {};
        virtual void onDestroy() {};

        virtual void onSaveState(void** pData, size_t* pSize) {};
        virtual void onConfigurationChanged() {};
        virtual void onLowMemory() {};

        virtual void onCreateWindow() {};
        virtual void onDestroyWindow() {};
        virtual void onGainFocus() {};
        virtual void onLostFocus() {};
    };
}
#endif
