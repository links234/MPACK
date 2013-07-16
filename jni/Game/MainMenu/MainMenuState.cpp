#include "MainMenuState.hpp"

#include "Application.hpp"
#include "TimeService.hpp"
#include "Texture2D.hpp"
#include "Global.hpp"
#include "GUIMenu.hpp"
#include "Particles.hpp"

using namespace Core;

namespace Game
{
	enum
	{
		GUIMENU_NOTHING,
		GUIMENU_BUTTON_NEWGAME,
		GUIMENU_BUTTON_HIGHSCORE,
		GUIMENU_BUTTON_CREDITS,
		GUIMENU_BUTTON_EXIT
	};

	MainMenu::MainMenu()
	{
		m_pButtonTexture=new Texture2D();
		m_pButtonTexture->Load("@Sprites/GUI_Button.tga",Bilinear);

		m_pBackgroundTexture=new Texture2D();
		m_pBackgroundTexture->Load("@Backgrounds/background.tga",Bilinear);

		m_pButtonSprite=new Sprite();
		m_pButtonSprite->SetTexture(m_pButtonTexture);

		m_pBackgroundSprite=new Sprite();
		m_pBackgroundSprite->SetTexture(m_pBackgroundTexture);
		m_pBackgroundSprite->SetSize(Render::GetScreenWidth(),Render::GetScreenHeight());
		m_pBackgroundSprite->m_position=Vector2f(Render::GetScreenWidth()*0.5f,Render::GetScreenHeight()*0.5f);
		m_pBackgroundSprite->m_spriteShadingType=SpriteVertex::NONE;

		m_pMenuGUI=new GUIMenu;
		m_pMenuGUI->m_sprite=m_pButtonSprite;

		m_pMenuGUI->AddButton("New Game",GUIMENU_BUTTON_NEWGAME);
		m_pMenuGUI->AddButton("Highscore",GUIMENU_BUTTON_HIGHSCORE);
		m_pMenuGUI->AddButton("Credits",GUIMENU_BUTTON_CREDITS);
		m_pMenuGUI->AddButton("Exit",GUIMENU_BUTTON_EXIT);
		m_pMenuGUI->BuildLayout();
	}

	int MainMenu::Update()
	{
		float lTimeStep = Global::pContext->pTimeService->Elapsed();

		int action=m_pMenuGUI->Update(lTimeStep);
		switch(action)
		{
			case GUIMENU_BUTTON_NEWGAME:
				return EVENT_MAINMENU_NEWGAME;
			break;
			case GUIMENU_BUTTON_HIGHSCORE:
				return EVENT_MAINMENU_HIGHSCORE;
			break;
			case GUIMENU_BUTTON_CREDITS:
				return EVENT_MAINMENU_CREDITS;
			break;
			case GUIMENU_BUTTON_EXIT:
				return EVENT_MAINMENU_EXIT;
			break;
		}

		return EVENT_NOTHING;
	}

	void MainMenu::Render()
	{
		m_pBackgroundSprite->Render();
		m_pMenuGUI->Render();
	}

	MainMenu::~MainMenu()
	{
		delete m_pMenuGUI;
		delete m_pButtonSprite;
		delete m_pButtonTexture;
	}
}
