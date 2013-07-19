#include "PlayGameState.hpp"

#include "Render.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "PhysicsService.hpp"
#include "Application.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"
#include "Particles.hpp"
#include "Camera2D.hpp"

namespace Game
{
	PlayGame::PlayGame()
	{
		m_pPGInputController = PGInputController::InitializeController();

		Global::pContext->pPhysicsService->callback=Physics_callback;

		m_backgroundTexture = new Texture2D;
		m_backgroundTexture->Load("@Backgrounds/spacebk1.png");
		m_backgroundTexture->SetWrapMode(GL_REPEAT,GL_REPEAT);

		m_background = new TiledBackground;
		m_background->SetTexture(m_backgroundTexture);
		m_background->SetShading(SpriteVertex::NONE);
		m_background->SetDepth(2.0f);
		m_background->SetUVScale(0.5f,0.5f);
		m_background->EnableCamera();

		m_particleTex = new Texture2D;
		m_particleTex->Load("@Sprites/GUI_Button.tga");

		m_pEmitter = new ParticleEmitterCircle;

		m_pEmitter->SetAngularVelocity(15.0f,17.0f);
		m_pEmitter->SetParticleLife(8.0f,10.0f);
		m_pEmitter->SetVelocity(10.0f,15.0f);
		m_pEmitter->SetTexture(m_particleTex);
		m_pEmitter->SetPosition(Vector2f(200.0f,200.0f));
		m_pEmitter->SetSpawnDelay(1.0f/10.0f);
		m_pEmitter->m_modifiers.push_back(new ParticleEffectorGravity());
		m_pEmitter->m_modifiers.push_back(new ParticleEffectorColor(Vector4f(1.0f,1.0f,0.0f,1.0f),Vector4f(0.0f,0.0f,1.0f,0.0f)));


		//Texture loading
		m_enemyTexture=new Texture2D;
		m_playerTexture=new Texture2D;

		m_enemyTexture->Load("@Sprites/Ships/enemy1.png");
		m_playerTexture->Load("@Sprites/Ships/Player.png");

		//Player sprite setup
		m_playerSprite=new Sprite;
		m_playerSprite->SetTexture(m_playerTexture);
		m_playerSprite->SetSize(50.0f,50.0f);
		m_playerSprite->SetShading(SpriteVertex::ALPHA_BLEND);

		//Player setup
		m_playerObject=new Player;
		m_playerObject->SetSprite(m_playerSprite);
		m_playerObject->SetPosition(Vector2f(Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5));

		//Enemy sprite setup
		m_enemySprite=new Sprite;
		m_enemySprite->SetTexture(m_enemyTexture);
		m_enemySprite->SetSize(100.0f,17.0f*4.0f);
		m_enemySprite->SetShading(SpriteVertex::ALPHA_BLEND);

		//Enemy setup
		m_enemyObject=new Enemy;
		m_enemyObject->SetSprite(m_enemySprite);
		m_enemyObject->SetPosition(Vector2f(50.0f,50.0f));

		//Camera setup
		Global::pActiveCamera=new Camera2D();
		Global::pActiveCamera->Link(m_playerObject);

		//should be deleted in final version
		m_testTexture=new Texture2D();
		m_testTexture->Load("@Sprites/Animations/explosion.png");

		m_testSprite=new AnimatedSprite();
		m_testSprite->m_position=Vector2f(Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5);
		m_testSprite->SetTexture(m_testTexture);
		m_testSprite->SetSize(200.0f,200.0f);
		m_testSprite->SetShading(SpriteVertex::ALPHA_BLEND);
		m_testSprite->SetLayer(1.0f);

		m_testSprite->BuildFrameGrid(5,4);
		m_testSprite->SetAnimation(Animation(0,20,10.0f));
	}

	int PlayGame::Update()
	{
		float lTimeStep = Global::pContext->pTimeService->Elapsed();

		m_pPGInputController->Update(lTimeStep);

		m_playerObject->SetLinearAcceleration(m_pPGInputController->GetMovementDirection());

		if(m_pPGInputController->IsUserRequestingExit())
		{
			return EVENT_PLAYGAME_EXIT;
		}
		return EVENT_NOTHING;
	}

	void PlayGame::Render()
	{
		//Debug::Print(Global::pFont,"X = %lf  Y = %lf",m_playerObject->GetLinearAcceleration().x,m_playerObject->GetLinearAcceleration().y);

		m_background->Render();

		m_pPGInputController->Render();
	}

	PlayGame::~PlayGame()
	{
		delete m_pPGInputController;

		delete m_particleTex;
		delete m_pEmitter;

		delete m_enemyTexture;
		delete m_playerTexture;

		delete m_enemySprite;
		delete m_playerSprite;

		delete m_enemyObject;
		delete m_playerObject;

		delete m_backgroundTexture;
		delete m_background;

		delete Global::pActiveCamera;
		Global::pActiveCamera=NULL;

		//should be deleted in final version
		delete m_testSprite;
		delete m_testTexture;
	}

	void PlayGame::Physics_callback(void *param1, void *param2)
	{
		/* 		This  piece of code is here to show you how NOT to cast pointer in diamond-structure inheritance
		 * Object *pobj1p=(Object*)param1;
		 * Object *pobj2p=(Object*)param2;
 	 	 *
		 * PObject *pobj1=(PObject*)param1;
		 * PObject *pobj2=(PObject*)param2;
		 * Object *obj1=(Object*)pobj1->GetUserData();
		 * Object *obj2=(Object*)pobj2->GetUserData();
		 */

		//ALLWAYS use dynamic_cast properly in situations like this!!
		PObject *pobj1=(PObject*)param1;
		PObject *pobj2=(PObject*)param2;
		PhysicalObject *tobj1=(PhysicalObject*)pobj1->GetUserData();
		PhysicalObject *tobj2=(PhysicalObject*)pobj2->GetUserData();
		Object *obj1=dynamic_cast<Object*>(tobj1);
		Object *obj2=dynamic_cast<Object*>(tobj2);

		obj1->m_debugInCollision=true;
		obj2->m_debugInCollision=true;
	}
}
