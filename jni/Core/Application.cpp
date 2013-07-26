#include "Application.hpp"
#include "GraphicsService.hpp"
#include "PhysicsService.hpp"
#include "SoundService.hpp"
#include "TimeService.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "Cursor.hpp"

#include "MainMenuState.hpp"
#include "PlayGameState.hpp"
#include "Log.hpp"

namespace Game
{
	Application::Application()
    {
		LOGI("Application::Aplication");
		m_pGameState = NULL;
		m_pSavedGameState = NULL;
    }

	Application::~Application()
    {
		LOGI("Application::~Application");
    }

	Core::Status Application::onActivate()
    {
		LOGI("Application::onActivate");
        // Starts services.
		if (Global::pContext->pGraphicsService->Start() != Core::STATUS_OK)
		{
			LOGE("Application::onActivate failed to start graphics service");
			return Core::STATUS_KO;
		}
		if (Global::pContext->pSoundService->Start() != Core::STATUS_OK)
		{
			LOGE("Application::onActivate failed to start sound service");
			return Core::STATUS_KO;
		}

		Global::pContext->pSoundService->PlayBGMPlaylist("@Sounds/playlist.txt");

		Global::pContext->pInputService->Reset();

		Global::pContext->pTimeService->Reset();

		m_pCursorTex = new Texture2D();
		m_pCursorTex->Load("@Sprites/Cursor.png",Bilinear);

#ifdef WINDOWS_PLATFORM
		Cursor::GetInstance()->SetIcon(m_pCursorTex);
		Cursor::GetInstance()->EnableAutohide();
#endif

		m_pGameState = new MainMenu;
		return Core::STATUS_OK;
    }

    void Application::onDeactivate()
    {
    	LOGI("Application::onDeactivate");
    	Global::pContext->pGraphicsService->Stop();
    	Global::pContext->pSoundService->Stop();

    	if(m_pGameState != NULL)
    	{
    		delete m_pGameState;
    	}

    	delete m_pCursorTex;
    }

    Core::Status Application::onStep()
    {
    	// Update clock
    	Global::pContext->pTimeService->Update();
    	const GLfloat &delta = Global::pContext->pTimeService->Elapsed();

    	Global::pContext->pInputService->Update();

    	// Debug messages here
		static GLfloat time=0.0f;
		time+=delta;
		Debug::Print(Global::pFont,"Elapsed time: %f",time);

    	// Update per-frame debug
    	Debug::InitFrame();

    	// Updates services
    	if(!m_pSavedGameState)
    	{
    		Global::pContext->pPhysicsService->Update(delta);
    	}
    	Global::pContext->pGraphicsService->Update(delta);

    	// Event dispatcher
    	int action=m_pGameState->Update();
    	switch(action)
    	{
    		case EVENT_MAINMENU_CONTINUE:
    			delete m_pGameState;
    			m_pGameState=m_pSavedGameState;
    			m_pGameState->Continue();
    			m_pGameState->Update();
    			m_pSavedGameState=NULL;
    		break;
    		case EVENT_MAINMENU_NEWGAME:
    			if(m_pSavedGameState)
    			{
    				delete m_pSavedGameState;
    				m_pSavedGameState=NULL;
    			}
    			delete m_pGameState;
    			m_pGameState=new PlayGame();
    			m_pGameState->Update();
    		break;
    		case EVENT_MAINMENU_HIGHSCORE:

    		break;
    		case EVENT_MAINMENU_CREDITS:

    		break;
    		case EVENT_MAINMENU_EXIT:
    			return STATUS_KO;
    		break;
    		case EVENT_PLAYGAME_PAUSE:
    			m_pGameState->Pause();
    			m_pSavedGameState=m_pGameState;
    			m_pGameState=new MainMenu(true);
    			m_pGameState->Update();
    		break;
    		case EVENT_PLAYGAME_EXIT:
				delete m_pGameState;
				m_pGameState=new MainMenu();
				m_pGameState->Update();
			break;
    	}

    	// Render current game state
    	m_pGameState->Render();

#ifdef WINDOWS_PLATFORM
    	Cursor::GetInstance()->Render();
#endif

    	// Render current scene and swap buffers
		if (Global::pContext->pGraphicsService->Render() != Core::STATUS_OK) {
			return Core::STATUS_KO;
		}
		return Core::STATUS_OK;
    }

    void Application::onStart()
    {
    	LOGI("Application::onStart");
    }

    void Application::onResume()
    {
    	LOGI("Application::onResume");
    }

    void Application::onPause()
    {
    	LOGI("Application::onPause");
    }

    void Application::onStop()
    {
    	LOGI("Application::onStop");
    }

    void Application::onDestroy()
    {
    	LOGI("Application::onDestroy");
    }

    void Application::onSaveState(void** pData, size_t* pSize)
    {
    	LOGI("Application::onSaveInstanceState");
    }

    void Application::onConfigurationChanged()
    {
    	LOGI("Application::onConfigurationChanged");
    }

    void Application::onLowMemory()
    {
    	LOGI("Application::onLowMemory");
    	LOGW("Please buy a better device!");
    }

    void Application::onCreateWindow()
    {
    	LOGI("Application::onCreateWindow");
    }

    void Application::onDestroyWindow()
    {
    	LOGI("Application::onDestroyWindow");
    }

    void Application::onGainFocus()
    {
    	LOGI("Application::onGainFocus");
    }

    void Application::onLostFocus()
    {
    	LOGI("Application::onLostFocus");
    }
}
