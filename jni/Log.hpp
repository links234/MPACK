#ifndef LOG_HPP
#define LOG_HPP

#include "Debug.hpp"

namespace Core
{
    class Log
    {
    public:
        static void Error(const char* pMessage, ...);
        static void Warn(const char* pMessage, ...);
        static void Info(const char* pMessage, ...);
        static void Debug(const char* pMessage, ...);
    };
}

#ifndef DEBUG
	#define LOGE(...)
	#define LOGW(...)
	#define LOGI(...)
	#define LOGD(...)
#else
	#define LOGE(...) Core::Log::Error(__VA_ARGS__)
	#define LOGW(...) Core::Log::Warn(__VA_ARGS__)
	#define LOGI(...) Core::Log::Info(__VA_ARGS__)
	#define LOGD(...) Core::Log::Debug(__VA_ARGS__)
#endif

#endif
