#include "Platform.hpp"
#include "Types.hpp"
#include "Context.hpp"
#include "Application.hpp"
#include "EventLoop.hpp"
#include "Graphics/GraphicsService.hpp"
#include "InputService.hpp"
#include "Sound/SoundService.hpp"
#include "Misc/TimeService.hpp"
#include "Physics/Physics.hpp"
#include "Misc/Random.hpp"
#include "Global.hpp"
#include "Debug/Debug.hpp"

#ifdef ANDROID_PLATFORM
void android_main(android_app* pApplication)
#elif 	defined(WINDOWS_PLATFORM)
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
#endif
{
	//Debug::WaitToConnect(5);

#ifdef ANDROID_PLATFORM
	Global::pAndroidApp=pApplication;
	Global::pAAssetManager=pApplication->activity->assetManager;
#endif

	Core::Random::Init();

    Core::TimeService *pTimeService = Core::TimeService::Initialize();
    Core::GraphicsService lGraphicsService;
    Core::SoundService lSoundService;
    Core::InputService lInputService;
    Core::PhysicsService lPhysicsService;
    Core::Context lContext={&lGraphicsService, &lInputService, &lSoundService, pTimeService, &lPhysicsService};

    Global::pContext = &lContext;

//Event loop parameter setup
#ifdef ANDROID_PLATFORM
    void *data=NULL;
#elif	defined(WINDOWS_PLATFORM)
    void *data=(void*)(&hInstance);
#endif

    Global::pEventLoop=Core::EventLoop::Initialize(data);
    Game::Application lApplication;
#ifdef ANDROID_PLATFORM
    Global::pEventLoop->Run(&lApplication);
#elif	defined(WINDOWS_PLATFORM)
    return Global::pEventLoop->Run(&lApplication);
#endif
}
