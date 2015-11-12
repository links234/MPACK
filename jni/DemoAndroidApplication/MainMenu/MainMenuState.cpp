#include "MainMenuState.hpp"

#include "MPACK.hpp"

using namespace MPACK;
using namespace MPACK::Core;
using namespace MPACK::Math;
using namespace MPACK::Graphics;

#include "DemoAndroidApplication.hpp"
#include "GameResources.hpp"
#include "GUIMenu.hpp"

namespace Demo
{
	enum
	{
		GUIMENU_NOTHING,
		GUIMENU_BUTTON_CONTINUE,
		GUIMENU_BUTTON_NEWGAME,
		GUIMENU_BUTTON_WATER,
		GUIMENU_BUTTON_HIGHSCORE,
		GUIMENU_BUTTON_CREDITS,
		GUIMENU_BUTTON_EXIT
	};

	MainMenu::MainMenu(bool isGamePaused)
	{
		m_pButtonTexture=new Texture2D();
		m_pButtonTexture->Load("[0]/GUI_Button.tga",FILTER_BILINEAR);

		m_pBackgroundTexture=new Texture2D();
		m_pBackgroundTexture->Load("@Backgrounds/background.tga",FILTER_BILINEAR);

		m_pButtonSprite=new Sprite();
		m_pButtonSprite->SetTexture(m_pButtonTexture);

		m_pBackgroundSprite=new Sprite();
		m_pBackgroundSprite->SetTexture(m_pBackgroundTexture);
		m_pBackgroundSprite->SetSize(Render::GetScreenWidth(),Render::GetScreenHeight());
		m_pBackgroundSprite->m_position=Vector2f(Render::GetScreenWidth()*0.5f,Render::GetScreenHeight()*0.5f);
		m_pBackgroundSprite->SetShading(SpriteVertex::NONE);

		m_pMenuGUI=new GUIMenu;
		m_pMenuGUI->m_sprite=m_pButtonSprite;

		if(isGamePaused)
		{
			m_pMenuGUI->AddButton("Continue",GUIMENU_BUTTON_CONTINUE);
		}
		m_pMenuGUI->AddButton("New Game",GUIMENU_BUTTON_NEWGAME);
		m_pMenuGUI->AddButton("Water", GUIMENU_BUTTON_WATER);
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
			case GUIMENU_BUTTON_CONTINUE:
				return EVENT_MAINMENU_CONTINUE;
			break;
			case GUIMENU_BUTTON_NEWGAME:
				return EVENT_MAINMENU_NEWGAME;
			break;
			case GUIMENU_BUTTON_WATER:
				return EVENT_MAINMENU_WATER;
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

		GameResources::GetFont()->SendString("TeStInG!!!:D ...",Render::GetScreenWidth()*0.4,Render::GetScreenHeight()*0.4);
	}

	void MainMenu::Pause()
	{
	}

	void MainMenu::Continue()
	{
	}

	MainMenu::~MainMenu()
	{
		delete m_pMenuGUI;
		delete m_pButtonSprite;
		delete m_pButtonTexture;
		delete m_pBackgroundTexture;
		delete m_pBackgroundSprite;
	}
}
