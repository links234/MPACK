#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP

#include "GameState.hpp"
#include "Texture2D.hpp"
#include "Sprite.hpp"
#include "Joystick.hpp"

using namespace Core;

namespace Game
{
	class PlayGame: public GameState
	{
	public:
		PlayGame();

		int Update();
		void Render();

		~PlayGame();

	private:
		static void onBackKey(void *pointer);

		bool m_requestExit;

		Texture2D 	*m_enemyTexture;
		Texture2D 	*m_playerTexture;
		Sprite		*m_playerSprite;

		Texture2D	*m_joystickInnerTex;
		Texture2D	*m_joystickOuterTex;
		Joystick 	*m_joystick;
	};
}

#endif
