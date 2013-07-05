#include "PlayGameState.hpp"

#include "Render.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "Application.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"
#include "Particles.hpp"
#include "Camera2D.hpp"

namespace Game
{
	PlayGame::PlayGame()
	{
		m_requestExit = false;

		Global::pContext->pInputService->Link_KEYBACK(Param1PtrCallbackStruct(onBackKey,this));

		m_particleTex = new Texture2D;
		m_particleTex->Load("@GUI_Button.tga");

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
		m_playerTexture=new Texture2D;
		m_joystickInnerTex=new Texture2D;
		m_joystickOuterTex=new Texture2D;

		m_playerTexture->Load("@Player.png");
		m_joystickInnerTex->Load("@joystick_inner.png");
		m_joystickOuterTex->Load("@joystick_outer.png");

		//Sprite setup
		m_playerSprite=new Sprite;
		m_playerSprite->m_position=Vector2f(Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5);
		m_playerSprite->SetTexture(m_playerTexture);
		m_playerSprite->SetSize(50.0f,50.0f);
		m_playerSprite->m_spriteShadingType=SpriteVertex::ALPHA_BLEND;

		//Player setup
		m_playerObject=new Player;
		m_playerObject->m_sprite=m_playerSprite;

		//Joystick setup
		m_joystick=new Joystick;
		m_joystick->SetTextures(m_joystickInnerTex,m_joystickOuterTex);
		m_joystick->SetMaxDistance(100.0f);

		//Camera setup
		Global::pActiveCamera=new Camera2D();
		Global::pActiveCamera->Link(m_playerObject);
	}

	int PlayGame::Update()
	{
		float lTimeStep = Global::pContext->pTimeService->Elapsed();

		m_joystick->Update();

		if(m_requestExit)
		{
			return EVENT_PLAYGAME_EXIT;
		}


		//NOT FINAL HERE!!!
		m_playerObject->m_acceleration=m_joystick->m_dir*5.0f;
		m_playerObject->m_direction=m_playerObject->m_velocity.Normalized();
		//NOT FINAL HERE!!!


		return EVENT_NOTHING;
	}

	void PlayGame::Render()
	{
		//Global::pFont->SendString("NEW GAME!",Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5,ALIGN_CENTER);

		m_joystick->Render();
	}

	PlayGame::~PlayGame()
	{
		delete m_particleTex;
		delete m_pEmitter;

		delete m_playerTexture;
		delete m_joystickInnerTex;
		delete m_joystickOuterTex;

		delete m_playerObject;

		delete m_joystick;

		delete Global::pActiveCamera;
		Global::pActiveCamera=NULL;
	}

	void PlayGame::onBackKey(void *pointer)
	{
		PlayGame *pPlayGame=(PlayGame*)(pointer);
		pPlayGame->m_requestExit=true;
	}
}
