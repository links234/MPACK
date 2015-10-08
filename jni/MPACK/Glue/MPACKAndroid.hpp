#ifndef MPACKANDROID_HPP
#define MPACKANDROID_HPP

#include "MPACKCommon.hpp"

#define MPACK_ANDROID_MAIN	\
	void android_main(android_app* MPACK_pApplication)

#define MPACK_ANDROID_INITIALIZE 												\
	MPACK::Core::Log::Initialize(); 											\
	MPACK::Core::Random::Init();												\
	MPACK::Global::pAndroidApp=MPACK_pApplication;								\
	MPACK::Global::pAAssetManager=MPACK_pApplication->activity->assetManager; 	\
	MPACK_FILLGLOBAL

#define MPACK_ANDROID_RUN(pApp,result) 													\
	void *MPACK_eventLoopData=NULL; 													\
	MPACK::Global::pEventLoop=MPACK::Core::EventLoop::Initialize(MPACK_eventLoopData); 	\
    result = MPACK::Global::pEventLoop->Run(pApp)

#define MPACK_ANDROID_RETURN(x)

#endif
