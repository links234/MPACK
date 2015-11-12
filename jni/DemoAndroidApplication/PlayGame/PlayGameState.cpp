#include "PlayGameState.hpp"

#include "Render.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "Physics.hpp"
#include "DemoAndroidApplication.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"
#include "Context.hpp"
#include "Particles.hpp"
#include "Camera2D.hpp"

using namespace MPACK;
using namespace MPACK::Core;
using namespace MPACK::Physics;
using namespace MPACK::Graphics;
using namespace MPACK::UI;

namespace Demo
{
	PlayGame::PlayGame()
	{
		m_pWorld = new World(1/60.0f,15);
		m_pWorld->EnableDebugDraw();

		m_pPGInputController = PGInputController::Initialize();
		m_pPGInputController->SetMaxAcceleration(500.0f);

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
		m_particleTex->Load("[0]/GUI_Button.tga");

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

		m_enemyTexture->Load("[0]/Ships/enemy1.png");
		m_playerTexture->Load("[0]/Ships/Player.png");

		//Player sprite setup
		m_playerSprite=new Sprite;
		m_playerSprite->SetTexture(m_playerTexture);
		m_playerSprite->SetSize(50.0f,50.0f);
		m_playerSprite->SetShading(SpriteVertex::ALPHA_BLEND);

		//Player setup
		m_playerObject=new Player(m_pWorld);
		m_playerObject->SetSprite(m_playerSprite);
		m_playerObject->SetPosition(Vector2f(Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5));

		//Enemy sprite setup
		m_enemySprite=new Sprite;
		m_enemySprite->SetTexture(m_enemyTexture);
		m_enemySprite->SetSize(100.0f,17.0f*4.0f);
		m_enemySprite->SetShading(SpriteVertex::COLOR_SUM_ALPHA_BLEND);
		m_enemySprite->SetColor(Vector4f(0.33f,0.33f,0.33f,1.0f));

		for(int i=0;i<=7;++i)
		{
			//Enemy setup
			m_enemyObject[0]=new Enemy(m_pWorld);
			m_enemyObject[0]->SetSprite(m_enemySprite);
			m_enemyObject[0]->SetPosition(Vector2f(50.0f,450.0f));

			//Enemy setup
			m_enemyObject[1]=new Enemy(m_pWorld);
			m_enemyObject[1]->SetSprite(m_enemySprite);
			m_enemyObject[1]->SetPosition(Vector2f(450.0f,50.0f));

			//Enemy setup
			m_enemyObject[2]=new Enemy(m_pWorld);
			m_enemyObject[2]->SetSprite(m_enemySprite);
			m_enemyObject[2]->SetPosition(Vector2f(450.0f,450.0f));


			//Enemy setup
			m_enemyObject[3]=new Enemy(m_pWorld);
			m_enemyObject[3]->SetSprite(m_enemySprite);
			m_enemyObject[3]->SetPosition(Vector2f(50.0f,50.0f));
		}

		//Camera setup
		Global::pActiveCamera=new Camera2D();
		Global::pActiveCamera->Link(m_playerObject);

		//should be deleted in final version
		m_testTexture=new Texture2D();
		m_testTexture->Load("[0]/Animations/explosion.png");

		m_testSprite=new AnimatedSprite();
		m_testSprite->m_position=Vector2f(Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5);
		m_testSprite->SetTexture(m_testTexture);
		m_testSprite->SetSize(200.0f,200.0f);
		m_testSprite->SetShading(SpriteVertex::ALPHA_BLEND);
		m_testSprite->SetLayer(1.0f);

		m_testSprite->BuildFrameGrid(5,4);
		m_testSprite->SetAnimation(Animation(0,20,10.0f));

		const float FRONT_LAYER=99910000.0f;
		m_UIMatch1Sprite = new Sprite();
		m_UIMatch1Sprite->SetTexture(m_playerTexture);
		m_UIMatch1Sprite->SetSize(300.0f,300.0f);
		m_UIMatch1Sprite->UIMatch(Anchor(Anchor::Get(Anchor::TopLeft)),Anchor(Anchor::Get(Anchor::TopLeft)));
		m_UIMatch1Sprite->SetLayer(FRONT_LAYER);
		m_UIMatch1Sprite->SetShading(SpriteVertex::ALPHA_BLEND);

		m_UIMatch2Sprite = new Sprite();
		m_UIMatch2Sprite->SetTexture(m_playerTexture);
		m_UIMatch2Sprite->SetSize(300.0f,300.0f);
		m_UIMatch2Sprite->UIMatch(Anchor(Anchor::Get(Anchor::BottomLeft)),Anchor(Anchor::Get(Anchor::BottomLeft)));
		m_UIMatch2Sprite->SetLayer(FRONT_LAYER);
		m_UIMatch2Sprite->SetShading(SpriteVertex::ALPHA_BLEND);

		m_UIMatch3Sprite = new Sprite();
		m_UIMatch3Sprite->SetTexture(m_playerTexture);
		m_UIMatch3Sprite->SetSize(300.0f,300.0f);
		m_UIMatch3Sprite->UIMatch(Anchor(Anchor::Get(Anchor::TopRight)),Anchor(Anchor::Get(Anchor::TopRight)));
		m_UIMatch3Sprite->SetLayer(FRONT_LAYER);
		m_UIMatch3Sprite->SetShading(SpriteVertex::ALPHA_BLEND);

		m_UIMatch4Sprite = new Sprite();
		m_UIMatch4Sprite->SetTexture(m_playerTexture);
		m_UIMatch4Sprite->SetSize(300.0f,300.0f);
		m_UIMatch4Sprite->UIMatch(Anchor(Anchor::Get(Anchor::BottomRight)),Anchor(Anchor::Get(Anchor::BottomRight)));
		m_UIMatch4Sprite->SetLayer(FRONT_LAYER);
		m_UIMatch4Sprite->SetShading(SpriteVertex::ALPHA_BLEND);

		m_pWorld->LinkCollisionCallback(CollisionCallbackStruct(Physics_collisionCallback, this));
	}

	int PlayGame::Update()
	{
		float lTimeStep = Global::pContext->pTimeService->Elapsed();
		float delta=lTimeStep;

		m_testSprite->Update(delta);

		m_pPGInputController->Update(lTimeStep);

		m_playerObject->SetLinearAcceleration(m_pPGInputController->GetMovementDirection());

		m_pWorld->Update(delta);

		Object::UpdateAll(delta);
		ParticleEmitter::UpdateAll(delta);
		Particle::UpdateAll(delta);
		Camera2D::UpdateAll(delta);

		if(m_pPGInputController->IsUserRequestingExit())
		{
			return EVENT_PLAYGAME_PAUSE;
		}
		return EVENT_NOTHING;
	}

	void PlayGame::Render()
	{
		//Debug::Print(Global::pFont,"X = %lf  Y = %lf",m_playerObject->GetLinearAcceleration().x,m_playerObject->GetLinearAcceleration().y);

		m_background->Render();
		//m_testSprite->Render();

		/*
		m_UIMatch1Sprite->Render();
		m_UIMatch2Sprite->Render();
		m_UIMatch3Sprite->Render();
		m_UIMatch4Sprite->Render();
		*/

		Batcher::EnableCamera();
		Object::RenderAll();
		Particle::RenderAll();
		m_pWorld->DebugDraw();
		Batcher::DisableCamera();

		m_pPGInputController->Render();
	}

	void PlayGame::Pause()
	{
		m_pPGInputController->Pause();
	}

	void PlayGame::Continue()
	{
		m_pPGInputController->Continue();
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

		delete m_backgroundTexture;
		delete m_background;

		delete Global::pActiveCamera;
		Global::pActiveCamera=NULL;

		Object::ClearAll();
		Particle::Cleanup();

		delete m_pWorld;

		//should be deleted in final version
		delete m_testSprite;
		delete m_testTexture;

		delete m_UIMatch1Sprite;
		delete m_UIMatch2Sprite;
		delete m_UIMatch3Sprite;
		delete m_UIMatch4Sprite;
	}

	void PlayGame::Physics_collisionCallback(void *userData, MPACK::Physics::Body *first, MPACK::Physics::Body *second, MPACK::Physics::CollisionInfo *collisionInfo)
	{
		PlayGame *state = (PlayGame*)(userData);

		VoidPointer *ptr1=static_cast<VoidPointer*>(first->userData);
		VoidPointer *ptr2=static_cast<VoidPointer*>(second->userData);

		if(ptr1->typeId==TypeId<Enemy*>())
		{
			Enemy *enemy=static_cast<Enemy*>(ptr1->pointer);
			enemy->inCollision=true;
		}
		if(ptr1->typeId==TypeId<Player*>())
		{
			Player *player=static_cast<Player*>(ptr1->pointer);
			player->inCollision=true;
		}

		if(ptr2->typeId==TypeId<Enemy*>())
		{
			Enemy *enemy=static_cast<Enemy*>(ptr2->pointer);
			enemy->inCollision=true;
		}
		if(ptr2->typeId==TypeId<Player*>())
		{
			Player *player=static_cast<Player*>(ptr2->pointer);
			player->inCollision=true;
		}
	}
}
