#include "Log.hpp"

#include "Platform.hpp"

#include <stdarg.h>
#ifdef ANDROID_PLATFORM
#include <android/log.h>
#endif

#define LOG_TAG "MPACK"

namespace Core
{
    void Log::Info(const char* pMessage, ...)
    {
#ifdef ANDROID_PLATFORM
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, pMessage, lVarArgs);
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "\n");
        va_end(lVarArgs);
#endif
    }

    void Log::Error(const char* pMessage, ...)
    {
#ifdef ANDROID_PLATFORM
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, pMessage, lVarArgs);
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "\n");
        va_end(lVarArgs);
#endif
    }

    void Log::Warn(const char* pMessage, ...)
    {
#ifdef ANDROID_PLATFORM
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_WARN, LOG_TAG, pMessage, lVarArgs);
        __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "\n");
        va_end(lVarArgs);
#endif
    }

    void Log::Debug(const char* pMessage, ...)
    {
#ifdef ANDROID_PLATFORM
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_DEBUG, LOG_TAG, pMessage, lVarArgs);
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "\n");
        va_end(lVarArgs);
#endif
    }
}
