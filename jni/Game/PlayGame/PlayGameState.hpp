#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP

#include "GameState.hpp"
#include "Texture2D.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"
#include "Joystick.hpp"
#include "Player.hpp"
#include "ParticleEmitterCircle.hpp"

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

		static void DOWN_callback(void *param1, void *param2);
		static void UP_callback(void *param1, void *param2);

		bool m_requestExit;

		Texture2D 	*m_enemyTexture;
		Texture2D 	*m_playerTexture;
		Sprite		*m_playerSprite;
		Player		*m_playerObject;

		Texture2D	*m_joystickInnerTex;
		Texture2D	*m_joystickOuterTex;
		Joystick 	*m_joystick;

		Finger		*m_fingers[2];
		Vector2f	m_firstPosition[2];
		Vector2f	m_lastFramePosition[2];
		GLfloat		m_firstScale;

		Texture2D				*m_particleTex;
		ParticleEmitterCircle 	*m_pEmitter;

		Texture2D		*m_testTexture;
		AnimatedSprite	*m_testSprite;
	};
}

#endif
