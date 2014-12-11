#ifndef MPACK_HPP
#define MPACK_HPP

#include "Global.hpp"

#include "Core.hpp"
#include "Debug.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "Math.hpp"
#include "Physics.hpp"
#include "Resources.hpp"
#include "Sound.hpp"
#include "Time.hpp"
#include "Misc.hpp"

#define MPACK_ANDROID_MAIN	void android_main(android_app* MPACK_pApplication)
#define MPACK_ANDROID_RETURN(x)

#define MPACK_WINDOWS_MAIN	int WINAPI WinMain(HINSTANCE MPACK_hInstance,	\
                   HINSTANCE MPACK_hPrevInstance,							\
                   LPSTR MPACK_cmdLine,										\
                   int MPACK_cmdShow)
#define MPACK_WINDOWS_RETURN(x)	return x

#define MPACK_LINUX_MAIN	int main()
#define MPACK_LINUX_RETURN(x)	return x

#ifdef ANDROID_PLATFORM
	#define MPACK_MAIN	MPACK_ANDROID_MAIN
	#define MPACK_RETURN(x) MPACK_ANDROID_RETURN(x)
#elif 	defined(WINDOWS_PLATFORM)
	#define MPACK_MAIN	MPACK_WINDOWS_MAIN
	#define MPACK_RETURN(x) MPACK_WINDOWS_RETURN(x)
#elif	defined(LINUX_PLATFORM)
	#define MPACK_MAIN	MPACK_LINUX_MAIN
	#define MPACK_RETURN(x) MPACK_LINUX_RETURN(x)
#endif

#define MPACK_FILLGLOBALCONTEXT	\
	MPACK::Time::TimeService *MPACK_pTimeService = MPACK::Time::TimeService::Initialize(); \
    Core::GraphicsService MPACK_lGraphicsService; \
    Core::SoundService MPACK_lSoundService; \
    Core::InputService MPACK_lInputService; \
    Core::PhysicsService MPACK_lPhysicsService; \
    Core::Context MPACK_lContext={&MPACK_lGraphicsService, &MPACK_lInputService, &MPACK_lSoundService, MPACK_pTimeService, &MPACK_lPhysicsService}; \
    Global::pContext = &MPACK_lContext

#ifdef ANDROID_PLATFORM
	#define MPACK_FILLGLOBAL \
		Global::pAndroidApp=MPACK_pApplication;	\
		Global::pAAssetManager=MPACK_pApplication->activity->assetManager; \
		MPACK_FILLGLOBALCONTEXT
#else
	#define MPACK_FILLGLOBAL \
		MPACK_FILLGLOBALCONTEXT
#endif

#if defined(ANDROID_PLATFORM) || defined(LINUX_PLATFORM)
	#define MPACK_INIT_EVENTLOOP_DATA void *MPACK_eventLoopData=NULL
#elif	defined(WINDOWS_PLATFORM)
	#define MPACK_INIT_EVENTLOOP_DATA void *MPACK_eventLoopData=(void*)(&MPACK_hInstance);
#endif

#define MPACK_RUN(pApp,result) \
	MPACK_INIT_EVENTLOOP_DATA; \
	Global::pEventLoop=Core::EventLoop::Initialize(MPACK_eventLoopData); \
    result = Global::pEventLoop->Run(pApp)

#define MPACK_INITIALIZE \
		Core::Log::Initialize(); \
		Core::Random::Init(); \
		MPACK_FILLGLOBAL

#define MPACK_SHUTDOWN \
		Core::Log::Destroy()

#endif
