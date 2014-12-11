#ifndef MPACK_CONTEXT_HPP
#define MPACK_CONTEXT_HPP

#include "Types.hpp"
#include "InputService.hpp"

namespace Core
{
	class GraphicsService;
	class SoundService;
    class PhysicsService;
}

namespace MPACK
{
	namespace Time
	{
		class TimeService;
	}
}

namespace Core
{
    class Context
    {
    public:
    	GraphicsService* 			pGraphicsService;
    	InputService*				pInputService;
    	SoundService*				pSoundService;
        MPACK::Time::TimeService* 	pTimeService;
        PhysicsService* 			pPhysicsService;
    };
}
#endif
