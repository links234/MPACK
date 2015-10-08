#ifndef MPACKLINUX_HPP
#define MPACKLINUX_HPP

#include "MPACKCommon.hpp"

#define MPACK_LINUX_MAIN													\
	int main(int MPACK_argc, char *MPACK_argv[])

#define MPACK_LINUX_INITIALIZE 												\
	for(int i=0;i<MPACK_argc;++i) 											\
	{ 																		\
		MPACK::Global::arguments.push_back(std::string(MPACK_argv[i]));		\
	} 																		\
	MPACK::Core::Log::Initialize(); 										\
	MPACK::Core::Random::Init(); 											\
	MPACK_FILLGLOBALCONTEXT

#define MPACK_LINUX_RUN(pApp,result) 													\
	void *MPACK_eventLoopData=NULL; 													\
	MPACK::Global::pEventLoop=MPACK::Core::EventLoop::Initialize(MPACK_eventLoopData); 	\
    result = MPACK::Global::pEventLoop->Run(pApp)

#define MPACK_LINUX_RETURN(x)												\
	return x

#endif
