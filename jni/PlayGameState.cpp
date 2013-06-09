#include "PlayGameState.hpp"

#include "Render.hpp"
#include "InputService.hpp"
#include "TimeService.hpp"
#include "Application.hpp"
#include "TextureMappedFont.hpp"
#include "Global.hpp"

namespace Game
{
	PlayGame::PlayGame()
	{
		m_requestExit=false;

		Global::pContext->pInputService->Link_KEYBACK(Param1PtrCallbackStruct(onBackKey,this));

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

		m_joystick=new Joystick;
		m_joystick->SetTextures(m_joystickInnerTex,m_joystickOuterTex);
		m_joystick->SetMaxDistance(100.0f);

		Render::EnableAlphaBlend();
	}

	int PlayGame::Update()
	{
		float lTimeStep = Global::pContext->pTimeService->Elapsed();

		m_joystick->Update();

		if(m_requestExit)
		{
			return EVENT_PLAYGAME_EXIT;
		}

		return EVENT_NOTHING;
	}

	void PlayGame::Render()
	{
		//Global::pFont->SendString("NEW GAME!",Render::GetScreenWidth()*0.5,Render::GetScreenHeight()*0.5,ALIGN_CENTER);

		m_playerSprite->Render();

		m_joystick->Render();

	}

	PlayGame::~PlayGame()
	{
		Render::DisableAlphaBlend();

		delete m_playerTexture;
		delete m_joystickInnerTex;
		delete m_joystickOuterTex;

		delete m_playerSprite;

		delete m_joystick;
	}

	void PlayGame::onBackKey(void *pointer)
	{
		PlayGame *pPlayGame=(PlayGame*)(pointer);
		pPlayGame->m_requestExit=true;
	}
}
