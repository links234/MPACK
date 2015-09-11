#ifndef MPACK_CONTEXT_HPP
#define MPACK_CONTEXT_HPP

#include "Types.hpp"
#include "InputService.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class GraphicsService;
	}

	namespace Sound
	{
		class SoundService;
	}

	namespace Time
	{
		class TimeService;
	}
}

namespace MPACK
{
	namespace Core
	{
		class Context
		{
		public:
			Graphics::GraphicsService* 		pGraphicsService;
			Input::InputService*			pInputService;
			Sound::SoundService*			pSoundService;
			Time::TimeService* 				pTimeService;
		};
	}
}
#endif
