#include "Log.hpp"

#include <stdarg.h>
#include <cstdio>

#include "FileLogger.hpp"

#ifdef ANDROID_PLATFORM
#include <android/log.h>
#elif	defined(WINDOWS_PLATFORM)
#include <windows.h>
#include <cstdio>
#endif

#define LOG_TAG 		"MPACK"
#define	 BUFFERSIZE 	65536

#ifdef WINDOWS_PLATFORM
FileLogger *pFileLogger;
#endif

namespace Core
{
	void Log::Initialize()
	{
#ifdef WINDOWS_PLATFORM
		pFileLogger=new FileLogger("log.html");
#endif
	}

	void Log::Destroy()
	{
#ifdef WINDOWS_PLATFORM
		delete pFileLogger;
#endif
	}

    void Log::Info(const char* pMessage, ...)
    {
        char buffer[BUFFERSIZE];
        va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
#ifdef ANDROID_PLATFORM
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, buffer);
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "\n");
#elif	defined(WINDOWS_PLATFORM)
		printf("Info: %s\n", buffer);
		pFileLogger->Print(FileLogger::Succes,"%s",buffer);
#endif
    }

    void Log::Error(const char* pMessage, ...)
    {
    	char buffer[BUFFERSIZE];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
#ifdef ANDROID_PLATFORM
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, buffer);
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "\n");
#elif	defined(WINDOWS_PLATFORM)
		printf("Error: %s\n", buffer);
		pFileLogger->Print(FileLogger::CriticalFailure,"%s",buffer);
#endif
    }

    void Log::Warn(const char* pMessage, ...)
    {
    	char buffer[BUFFERSIZE];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
#ifdef ANDROID_PLATFORM
		__android_log_print(ANDROID_LOG_WARN, LOG_TAG, buffer);
		__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "\n");
#elif	defined(WINDOWS_PLATFORM)
		printf("Info: %s\n", buffer);
		pFileLogger->Print(FileLogger::Warning,"%s",buffer);
#endif
    }

    void Log::Debug(const char* pMessage, ...)
    {
    	char buffer[BUFFERSIZE];
		va_list lVarArgs;
		va_start(lVarArgs, pMessage);
		vsprintf (buffer,pMessage,lVarArgs);
		va_end(lVarArgs);
		
#ifdef ANDROID_PLATFORM
		__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, buffer);
		__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "\n");
#elif	defined(WINDOWS_PLATFORM)
		printf("Info: %s\n", buffer);
		pFileLogger->Print(FileLogger::Information,"%s",buffer);
#endif
    }
}
