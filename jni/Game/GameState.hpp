#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

namespace Game
{
	class GameState
	{
	public:
		GameState();

		virtual int Update()=0;
		virtual void Render()=0;

		virtual ~GameState();
	};
}

#endif
