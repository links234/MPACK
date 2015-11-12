#ifndef MPACK_HPP
#define MPACK_HPP

#include "MPACKAndroid.hpp"
#include "MPACKLinux.hpp"
#include "MPACKWindows.hpp"

#if defined(ANDROID_PLATFORM)
	#define MPACK_MAIN	MPACK_ANDROID_MAIN
	#define MPACK_INITIALIZE MPACK_ANDROID_INITIALIZE
	#define MPACK_RUN(pApp,result) MPACK_ANDROID_RUN(pApp,result)
	#define MPACK_RETURN(x) MPACK_ANDROID_RETURN(x)
#elif 	defined(WINDOWS_PLATFORM)
	#define MPACK_MAIN	MPACK_WINDOWS_MAIN
	#define MPACK_INITIALIZE MPACK_WINDOWS_INITIALIZE
	#define MPACK_RUN(pApp,result) MPACK_WINDOWS_RUN(pApp,result)
	#define MPACK_RETURN(x) MPACK_WINDOWS_RETURN(x)
#elif	defined(LINUX_PLATFORM)
	#define MPACK_MAIN	MPACK_LINUX_MAIN
	#define MPACK_INITIALIZE MPACK_LINUX_INITIALIZE
	#define MPACK_RUN(pApp,result) MPACK_LINUX_RUN(pApp,result)
	#define MPACK_RETURN(x) MPACK_LINUX_RETURN(x)
#endif

#define MPACK_SHUTDOWN 							\
		delete MPACK_pInputService; 			\
		delete MPACK_pGraphicsService; 			\
		delete MPACK_pSoundService; 			\
		delete MPACK_pTimeService; 				\
		MPACK::Core::Log::Destroy();			\
		MPACK::Core::Console::Reset();			\
		MPACK::Core::Console::Cleanup()
#endif
