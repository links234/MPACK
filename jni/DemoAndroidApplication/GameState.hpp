#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

namespace Demo
{
	class GameState
	{
	public:
		GameState();

		virtual int Update()=0;
		virtual void Render()=0;

		virtual void Pause()=0;
		virtual void Continue()=0;

		virtual ~GameState();
	};
}

#endif
