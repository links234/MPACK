#include "Log.hpp"

#include "Platform.hpp"

#include <stdarg.h>

#ifdef ANDROID_PLATFORM
#include <android/log.h>
#elif	defined(WINDOWS_PLATFORM)
#include <windows.h>
#include <cstdio>
#endif

#define LOG_TAG 		"MPACK"
#define	 BUFFERSIZE 	512

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
#elif	defined(WINDOWS_PLATFORM)
        char buffer[BUFFERSIZE];
        va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
		printf("Info: %s\n", buffer);
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
#elif	defined(WINDOWS_PLATFORM)
        char buffer[BUFFERSIZE];
        va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
		printf("ERROR: %s\n", buffer);
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
#elif	defined(WINDOWS_PLATFORM)
        char buffer[BUFFERSIZE];
        va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
		printf("Warn: %s\n", buffer);
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
#elif	defined(WINDOWS_PLATFORM)
        char buffer[BUFFERSIZE];
        va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
		printf("Debug: %s\n", buffer);
		
		//MessageBox(NULL,buffer,"Debug message",MB_OK);
#endif
    }
}
