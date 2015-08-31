#include "DemoApplication.hpp"
#include "GraphicsService.hpp"
#include "PhysicsService.hpp"
#include "Sound.hpp"
#include "TimeService.hpp"
#include "Context.hpp"
#include "Global.hpp"
#include "EventLoop.hpp"
#include "IniFile.hpp"
#include "GoogleAds.hpp"

#include "GameResources.hpp"
#include "MainMenuState.hpp"
#include "PlayGameState.hpp"
#include "Log.hpp"

using namespace MPACK;
using namespace MPACK::Core;
using namespace MPACK::Graphics;

#ifdef ANDROID_PLATFORM
MPACK::ADS::GoogleAds *test;
#endif

#define MPACK_TESTING

namespace Game
{
	DemoApplication::DemoApplication()
    {
		m_pGameState = NULL;
		m_pSavedGameState = NULL;
		m_pCursorTex = NULL;
    }

	DemoApplication::~DemoApplication()
    {
		LOGI("DemoApplication::~DemoApplication()");
    }

	MPACK::Core::ReturnValue DemoApplication::onActivate()
    {
		LOGI("DemoApplication::onActivate()");

		GameResources::InitMVFS();

        // Starts services.
		if (Global::pContext->pGraphicsService->Start() != Core::RETURN_VALUE_OK)
		{
			LOGE("DemoApplication::onActivate failed to start graphics service");
			return Core::RETURN_VALUE_KO;
		}
		PostEffect::ClearFX();
		PostEffect::PushFX(PostEffect::FXAAI);

		if (Global::pContext->pSoundService->Start() != Core::RETURN_VALUE_OK)
		{
			LOGE("DemoApplication::onActivate failed to start sound service");
			return Core::RETURN_VALUE_KO;
		}

		Global::pContext->pInputService->Reset();

		Global::pContext->pTimeService->Reset();

		GameResources::Init();

		m_pCursorTex = new Texture2D();
		m_pCursorTex->Load("[0]/Cursor.png",Bilinear);

#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
		Global::pEventLoop->HideCursor();

		CursorDrawer::GetInstance()->SetIcon(m_pCursorTex);
		CursorDrawer::GetInstance()->Show();
		CursorDrawer::GetInstance()->EnableAutohide();
#endif

		m_pGameState = new MainMenu;

		test = new MPACK::ADS::GoogleAds();

		return Core::RETURN_VALUE_OK;
    }

    void DemoApplication::onDeactivate()
    {
    	GameResources::Uninit();

    	LOGI("DemoApplication::onDeactivate()");
    	MPACK::Global::pContext->pGraphicsService->Stop();
    	MPACK::Global::pContext->pSoundService->Stop();

    	MPACK::Global::pEventLoop->ShowCursor();

    	if(m_pGameState != NULL)
    	{
    		delete m_pGameState;
    	}

    	delete m_pCursorTex;
    }

    Core::ReturnValue DemoApplication::onStep()
    {
    	//test->showVideoInterstitial();

#ifdef MPACK_TESTING
    	static bool started=false;
    	static Time::Timer *timer=Time::Timer::Create();
    	static Sound::AudioPlayer *sound=new Sound::AudioPlayer();
    	static string message="";

    	if(!started)
    	{
    		started=true;

    		timer->Start();

    		sound->LoadFD("@Sounds/bgm.mp3");
    		sound->AddToGroup("background");

    		Sound::GroupController::Get("background")->Play()->Start();

    		/*
    		IniFile ini;
			ini.Load("@local/menu.ini");

			LOGD("::key = <%s>",ini.GetObject("key")->GetValue().c_str());

			LOGD("Section1::some_path = <%s>",ini.GetSection("Section1")->GetObject("some_path")->GetValue().c_str());
			LOGD("Section1::var1 = <%s>",ini.GetSection("Section1")->GetObject("var1")->GetValue().c_str());
			LOGD("Section1::var2 = <%s>",ini.GetSection("Section1")->GetObject("var2")->GetValue().c_str());
			LOGD("Section2::nr_of_enemies = <%s>",ini.GetSection("Section2")->GetObject("nr_of_enemies")->GetValue().c_str());

			message = ini.GetSection("ModifyHere")->GetObject("ThisKey")->GetValue();
			*/
    	}
    	static int state=0;
    	if(timer->Time()>10.0f && state==0)
    	{
    		LOGE("TOGGLE GROUPCONTROLLER MUTE");
    		++state;
    		Sound::GroupController::Get("background")->Volume()->ToggleMute();
    	}
    	if(timer->Time()>15.0f && state==1)
		{
    		LOGE("TOGGLE GROUPCONTROLLER MUTE");
			++state;
			//Sound::OutputMixer::GetOutputMixer()->Volume()->ToggleMute();
    		Sound::GroupController::Get("background")->Volume()->ToggleMute();
		}
    	if(timer->Time()>20.0f && state==2)
    	{
    		LOGE("Reset and 0.2 volume");
    		++state;
    		Sound::GroupController::Get("background")->Volume()->Set(0.2);
    		Sound::GroupController::Get("background")->Play()->Start();
    	}
#endif

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
#ifdef ANDROID_PLATFORM
    			test->showSmartBanner();
#endif
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
#ifdef ANDROID_PLATFORM
    			test->hideSmartBanner();
    			test->hideLargeBanner();
#endif
    			m_pGameState=new PlayGame();
    			m_pGameState->Update();
    		break;
    		case EVENT_MAINMENU_HIGHSCORE:
#ifdef ANDROID_PLATFORM
    			test->showLargeBanner();
#endif
    		break;
    		case EVENT_MAINMENU_CREDITS:
#ifdef ANDROID_PLATFORM
    			test->showTextImageVideoInterstitial();
#endif
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

#ifdef MPACK_TESTING
    	Debug::Print(Global::pFont,"%s",message.c_str());
#endif

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

    void DemoApplication::onStart()
    {
    	LOGI("DemoApplication::onStart");
    }

    void DemoApplication::onResume()
    {
    	LOGI("DemoApplication::onResume");
    }

    void DemoApplication::onPause()
    {
    	LOGI("DemoApplication::onPause");
    }

    void DemoApplication::onStop()
    {
    	LOGI("DemoApplication::onStop");
    }

    void DemoApplication::onDestroy()
    {
    	LOGI("DemoApplication::onDestroy");
    }

    void DemoApplication::onSaveState(void** pData, size_t* pSize)
    {
    	LOGI("DemoApplication::onSaveInstanceState");
    }

    void DemoApplication::onConfigurationChanged()
    {
    	LOGI("DemoApplication::onConfigurationChanged");
    }

    void DemoApplication::onLowMemory()
    {
    	LOGI("DemoApplication::onLowMemory");
    	LOGW("Please buy a better device!");
    }

    void DemoApplication::onCreateWindow()
    {
    	LOGI("DemoApplication::onCreateWindow");
    }

    void DemoApplication::onDestroyWindow()
    {
    	LOGI("DemoApplication::onDestroyWindow");
    }

    void DemoApplication::onGainFocus()
    {
    	LOGI("DemoApplication::onGainFocus");
    }

    void DemoApplication::onLostFocus()
    {
    	LOGI("DemoApplication::onLostFocus");
    }
}
