#ifndef MPACKCOMMON_HPP
#define MPACKCOMMON_HPP

#include "Global.hpp"

#include "Algorithm.hpp"
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

#include "GoogleAds.hpp"

#define MPACK_FORCE_SEMICOLON 			\
	do 									\
	{ 									\
										\
	} while(0)

#define MPACK_RUN_COMMON(UserApplication,result) 											\
	UserApplication *MPACK_pUserApplication = new UserApplication(); 						\
	if (MPACK_pUserApplication->GetType() == MPACK::Core::APP_ANDROID)						\
	{																						\
		MPACK::Global::pEventLoop=MPACK::Core::EventLoop::Initialize(MPACK_eventLoopData); 	\
    	result = MPACK::Global::pEventLoop->Run(MPACK_pUserApplication); 					\
    	delete MPACK::Global::pEventLoop; 													\
	}																						\
	else if (MPACK_pUserApplication->GetType() == MPACK::Core::APP_CONSOLE) 				\
	{																						\
		MPACK::Global::pEventLoop=NULL;														\
		result = MPACK_pUserApplication->Main();											\
	}																						\
	delete MPACK_pUserApplication

#define MPACK_FILLGLOBALCONTEXT																\
	MPACK::Time::TimeService *MPACK_pTimeService = MPACK::Time::TimeService::Initialize(); 	\
    MPACK::Graphics::GraphicsService 	*MPACK_pGraphicsService; 							\
    MPACK_pGraphicsService = new MPACK::Graphics::GraphicsService(); 						\
    MPACK::Sound::SoundService 			*MPACK_pSoundService; 								\
    MPACK_pSoundService = new MPACK::Sound::SoundService(); 								\
    MPACK::Input::InputService 			*MPACK_pInputService; 								\
    MPACK_pInputService = new MPACK::Input::InputService(); 								\
    MPACK::Core::Context MPACK_lContext={MPACK_pGraphicsService, MPACK_pInputService, 		\
										 MPACK_pSoundService, MPACK_pTimeService}; 			\
    MPACK::Global::pContext = &MPACK_lContext

#endif
