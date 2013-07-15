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

		//Setup input surface
		m_fingers[0]=m_fingers[1]=NULL;
		Global::pContext->pInputService->Link_FDOWN(Param2PtrCallbackStruct(DOWN_callback,this));
		Global::pContext->pInputService->Link_FUP(Param2PtrCallbackStruct(UP_callback,this));

		//should be deleted in final version
		m_testTexture=new Texture2D();
		m_testTexture->Load("@explosion.png");

		m_testSprite=new AnimatedSprite();
		m_testSprite->m_position=Vector2f(Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5);
		m_testSprite->SetTexture(m_testTexture);
		m_testSprite->SetSize(200.0f,200.0f);
		m_testSprite->m_spriteShadingType=SpriteVertex::ALPHA_BLEND;
		m_testSprite->m_layer=1.0f;

		m_testSprite->BuildFrameGrid(5,4);
		m_testSprite->SetAnimation(Animation(0,20,10.0f));
	}

	int PlayGame::Update()
	{
		float lTimeStep = Global::pContext->pTimeService->Elapsed();

		m_joystick->Update();

		if(m_fingers[1])
		{
			GLfloat firstDistance=m_firstPosition[0].Distance(m_firstPosition[1]);
			GLfloat currentDistance=m_fingers[0]->m_pos.Distance(m_fingers[1]->m_pos);
			GLfloat ratio=currentDistance/firstDistance;
			Global::pActiveCamera->SetScale(m_firstScale*ratio);

			GLfloat lastAngle=(m_lastFramePosition[1]-m_lastFramePosition[0]).Angle();
			GLfloat	currentAngle=(m_fingers[1]->m_pos-m_fingers[0]->m_pos).Angle();
			GLfloat angle=currentAngle-lastAngle;
			Global::pActiveCamera->RotateDirection(angle);
		}

		if(m_fingers[0])
		{
			m_lastFramePosition[0]=m_fingers[0]->m_pos;
		}
		if(m_fingers[1])
		{
			m_lastFramePosition[1]=m_fingers[1]->m_pos;
		}

		//NOT FINAL HERE!!!
		m_playerObject->m_acceleration=m_joystick->m_dir*5.0f;
		m_playerObject->m_acceleration.Rotate(Global::pActiveCamera->GetDirection().Angle());
		m_playerObject->m_direction=m_playerObject->m_velocity.Normalized();
		//NOT FINAL HERE!!!

		if(m_requestExit)
		{
			return EVENT_PLAYGAME_EXIT;
		}
		return EVENT_NOTHING;
	}

	void PlayGame::Render()
	{
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

		//should be deleted in final version
		delete m_testSprite;
		delete m_testTexture;
	}

	void PlayGame::onBackKey(void *pointer)
	{
		PlayGame *pPlayGame=(PlayGame*)(pointer);
		pPlayGame->m_requestExit=true;
	}

	void PlayGame::DOWN_callback(void *param1, void *param2)
	{
		PlayGame *pPlayGame=(PlayGame*)(param1);
		Finger *pFinger=(Finger*)(param2);
		if(pFinger->m_flag==FF_LOCKED)
		{
			return;
		}
		if(pPlayGame->m_fingers[0]==NULL)
		{
			pFinger->m_flag=FF_LOCKED;
			pPlayGame->m_firstPosition[0]=pFinger->m_pos;
			pPlayGame->m_lastFramePosition[0]=pFinger->m_pos;
			pPlayGame->m_fingers[0]=pFinger;
			return;
		}
		if(pPlayGame->m_fingers[1]==NULL)
		{
			pFinger->m_flag==FF_LOCKED;
			pPlayGame->m_firstPosition[1]=pFinger->m_pos;
			pPlayGame->m_lastFramePosition[1]=pFinger->m_pos;
			pPlayGame->m_fingers[1]=pFinger;
			pPlayGame->m_firstScale=Global::pActiveCamera->GetScale();
		}
	}

	void PlayGame::UP_callback(void *param1, void *param2)
	{
		PlayGame *pPlayGame=(PlayGame*)(param1);
		Finger *pFinger=(Finger*)(param2);
		if(pPlayGame->m_fingers[1]==pFinger)
		{
			pFinger->m_flag=FF_FREE;
			pPlayGame->m_fingers[1]=NULL;
		}
		if(pPlayGame->m_fingers[0]==pFinger)
		{
			pFinger->m_flag==FF_FREE;
			if(pPlayGame->m_fingers[1]!=NULL)
			{
				pPlayGame->m_fingers[0]=pPlayGame->m_fingers[1];
				pPlayGame->m_firstPosition[0]=pPlayGame->m_firstPosition[1];
				pPlayGame->m_lastFramePosition[0]=pPlayGame->m_lastFramePosition[1];
				pPlayGame->m_fingers[1]=NULL;
			}
			else
			{
				pPlayGame->m_fingers[0]=NULL;
			}
		}
	}
}
