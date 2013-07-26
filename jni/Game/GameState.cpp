#include "GameState.hpp"

#include "Platform.hpp"
#include "Context.hpp"
#include "InputService.hpp"
#include "Particles.hpp"
#include "Global.hpp"

namespace Game
{
	GameState::GameState()
	{
	}

	GameState::~GameState()
	{
#ifdef ANDROID_PLATFORM
		Global::pContext->pInputService->ClearLinks();
#elif 	defined(WINDOWS_PLATFORM)

#endif
	}
}
