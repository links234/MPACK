#include "GameState.hpp"

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
		Global::pContext->pInputService->ClearLinks();

		Particle::Clear();
	}
}
