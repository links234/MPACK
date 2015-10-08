#ifndef MPACKWINDOWS_HPP
#define MPACKWINDOWS_HPP

#include "MPACKCommon.hpp"

#define MPACK_WINDOWS_MAIN								\
	int WINAPI WinMain(HINSTANCE MPACK_hInstance,		\
						HINSTANCE MPACK_hPrevInstance,	\
						LPSTR MPACK_cmdLine,			\
						int MPACK_cmdShow)

#define MPACK_WINDOWS_INITIALIZE 												\
	LPWSTR *MPACK_szArgList; 													\
	int MPACK_argCount; 														\
	MPACK_szArgList = CommandLineToArgvW(GetCommandLine(), &MPACK_argCount);	\
	if (MPACK_szArgList == NULL) 												\
	{ 																			\
		return 1; 																\
	} 																			\
	for(int i=0;i<MPACK_argCount;++i) 											\
	{ 																			\
		MPACK::Global::arguments.push_back(std::string(MPACK_szArgList[i]));	\
	} 																			\
	LocalFree(MPACK_szArgList); 												\
																				\
	MPACK::Core::Log::Initialize(); 											\
	MPACK::Core::Random::Init();												\
	MPACK_FILLGLOBALCONTEXT

#define MPACK_WINDOWS_RUN(pApp,result) 													\
	void *MPACK_eventLoopData=(void*)(&MPACK_hInstance); 								\
	MPACK::Global::pEventLoop=MPACK::Core::EventLoop::Initialize(MPACK_eventLoopData); 	\
    result = MPACK::Global::pEventLoop->Run(pApp)

#define MPACK_WINDOWS_RETURN(x)													\
	return x

#endif
