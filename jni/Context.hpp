#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Types.hpp"

#include "InputService.hpp"

namespace Core
{
	class GraphicsService;
	class SoundService;
    class TimeService;
    class PhysicsService;

    struct Context
    {
    	GraphicsService* 	pGraphicsService;
    	InputService*		pInputService;
    	SoundService*		pSoundService;
        TimeService* 		pTimeService;
        PhysicsService* 	pPhysicsService;
    };
}
#endif
