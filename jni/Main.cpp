#include "Types.hpp"
#include "Log.hpp"
#include "Context.hpp"
#include "Application.hpp"
#include "EventLoop.hpp"
#include "Graphics/GraphicsService.hpp"
#include "InputService.hpp"
#include "Sound/SoundService.hpp"
#include "Time/TimeService.hpp"
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
#elif	defined(LINUX_PLATFORM)
int main()
#endif
{
	Core::Log::Initialize();

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
#if defined(ANDROID_PLATFORM) || defined(LINUX_PLATFORM)
    void *data=NULL;
#elif	defined(WINDOWS_PLATFORM)
    void *data=(void*)(&hInstance);
#endif

    Global::pEventLoop=Core::EventLoop::Initialize(data);
    Game::Application lApplication;
    int result = Global::pEventLoop->Run(&lApplication);

    Core::Log::Destroy();

#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    return result;
#endif
}
