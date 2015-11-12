#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP

#include "MPACK.hpp"

#include "GameState.hpp"
#include "PGInputController.hpp"

#include "Player.hpp"
#include "Enemy.hpp"

using namespace MPACK::Core;

namespace Demo
{
	class PlayGame: public GameState
	{
	public:
		PlayGame();

		int Update();
		void Render();

		void Pause();
		void Continue();

		~PlayGame();

	private:
		static void Physics_collisionCallback(void *userData, MPACK::Physics::Body *first, MPACK::Physics::Body *second, MPACK::Physics::CollisionInfo *collisionInfo);

		PGInputController		*m_pPGInputController;

		MPACK::Graphics::Texture2D			*m_backgroundTexture;
		MPACK::Graphics::TiledBackground	*m_background;

		MPACK::Graphics::Texture2D 			*m_playerTexture;
		MPACK::Graphics::Sprite				*m_playerSprite;
		Player								*m_playerObject;

		MPACK::Graphics::Texture2D 		*m_enemyTexture;
		MPACK::Graphics::Sprite			*m_enemySprite;
		Enemy							*m_enemyObject[4];

		MPACK::Graphics::Texture2D				*m_particleTex;
		MPACK::Graphics::ParticleEmitterCircle 	*m_pEmitter;

		MPACK::Graphics::Texture2D		*m_testTexture;
		MPACK::Graphics::AnimatedSprite	*m_testSprite;

		MPACK::Graphics::Sprite			*m_UIMatch1Sprite;
		MPACK::Graphics::Sprite			*m_UIMatch2Sprite;
		MPACK::Graphics::Sprite			*m_UIMatch3Sprite;
		MPACK::Graphics::Sprite			*m_UIMatch4Sprite;

		MPACK::Physics::World			*m_pWorld;
	};
}

#endif
