#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Types.hpp"

namespace Core
{
	class GraphicsService;
	class InputService;
	class SoundService;
    class TimeService;

    struct Context
    {
    	GraphicsService* 	pGraphicsService;
    	InputService*		pInputService;
    	SoundService*		pSoundService;
        TimeService* 		pTimeService;
    };
}
#endif
