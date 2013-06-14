#include "GameState.hpp"

#include "InputService.hpp"
#include "Global.hpp"

namespace Game
{
	GameState::GameState()
	{
	}

	GameState::~GameState()
	{
		Global::pContext->pInputService->ClearLinks();
	}
}
