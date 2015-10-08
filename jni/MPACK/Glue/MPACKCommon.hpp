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

#define MPACK_FORCE_SEMICOLON 			\
	do 									\
	{ 									\
										\
	} while(0)

#define MPACK_FILLGLOBALCONTEXT																\
	MPACK::Time::TimeService *MPACK_pTimeService = MPACK::Time::TimeService::Initialize();	\
    MPACK::Graphics::GraphicsService 	MPACK_lGraphicsService; 							\
    MPACK::Sound::SoundService 			MPACK_lSoundService; 								\
    MPACK::Input::InputService 			MPACK_lInputService; 								\
    MPACK::Core::Context MPACK_lContext = { &MPACK_lGraphicsService, 						\
											&MPACK_lInputService, 							\
											&MPACK_lSoundService, 							\
											MPACK_pTimeService}; 							\
    MPACK::Global::pContext = &MPACK_lContext

#endif
