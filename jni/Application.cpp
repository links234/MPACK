#include "Application.hpp"
#include "GraphicsService.hpp"
#include "PhysicsService.hpp"
#include "SoundService.hpp"
#include "TimeService.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "EventLoop.hpp"

#include "MainMenuState.hpp"
#include "PlayGameState.hpp"
#include "Log.hpp"

using namespace MPACK;
using namespace MPACK::Graphics;

namespace Game
{
	Application::Application()
    {
		m_pGameState = NULL;
		m_pSavedGameState = NULL;
		m_pCursorTex = NULL;
    }

	Application::~Application()
    {
		LOGI("Application::~Application");
    }

	MPACK::Core::ReturnValue Application::onActivate()
    {
		LOGI("Application::onActivate");
        // Starts services.
		if (Global::pContext->pGraphicsService->Start() != Core::RETURN_VALUE_OK)
		{
			LOGE("Application::onActivate failed to start graphics service");
			return Core::RETURN_VALUE_KO;
		}
		PostEffect::ClearFX();
		PostEffect::PushFX(PostEffect::FXAAI);

		if (Global::pContext->pSoundService->Start() != Core::RETURN_VALUE_OK)
		{
			LOGE("Application::onActivate failed to start sound service");
			return Core::RETURN_VALUE_KO;
		}

		Global::pContext->pSoundService->PlayBGMPlaylist("@Sounds/playlist.txt");

		Global::pContext->pInputService->Reset();

		Global::pContext->pTimeService->Reset();

		m_pCursorTex = new Texture2D();
		m_pCursorTex->Load("@Sprites/Cursor.png",Bilinear);

#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
		Global::pEventLoop->HideCursor();

		CursorDrawer::GetInstance()->SetIcon(m_pCursorTex);
		CursorDrawer::GetInstance()->Show();
		CursorDrawer::GetInstance()->EnableAutohide();
#endif

		m_pGameState = new MainMenu;
		return Core::RETURN_VALUE_OK;
    }

    void Application::onDeactivate()
    {
    	LOGI("Application::onDeactivate");
    	MPACK::Global::pContext->pGraphicsService->Stop();
    	MPACK::Global::pContext->pSoundService->Stop();

    	MPACK::Global::pEventLoop->ShowCursor();

    	if(m_pGameState != NULL)
    	{
    		delete m_pGameState;
    	}

    	delete m_pCursorTex;
    }

    Core::ReturnValue Application::onStep()
    {
    	// Update clock
    	const GLfloat &delta = Global::pContext->pTimeService->Elapsed();



    	// Debug messages here
		Debug::Print(Global::pFont,"Frame time: %f (%f FPS)",delta,1.0f/delta);

    	// Update per-frame debug messages
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
    			return RETURN_VALUE_KO;
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

#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    	CursorDrawer::GetInstance()->Update();
    	CursorDrawer::GetInstance()->Render();
#endif

    	// Render current scene and swap buffers
		if (Global::pContext->pGraphicsService->Render() != Core::RETURN_VALUE_OK) {
			return Core::RETURN_VALUE_KO;
		}

		return Core::RETURN_VALUE_OK;
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
