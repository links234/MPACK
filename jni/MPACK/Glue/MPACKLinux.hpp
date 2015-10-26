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

#define MPACK_LINUX_RUN(UserApplication,result) 							\
	void *MPACK_eventLoopData=NULL; 										\
	MPACK_RUN_COMMON(UserApplication,result)

#define MPACK_LINUX_RETURN(x)												\
	return x

#endif
