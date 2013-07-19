#include "Platform.hpp"
#include "Context.hpp"
#include "Application.hpp"
#include "EventLoop.hpp"
#include "GraphicsService.hpp"
#include "InputService.hpp"
#include "SoundService.hpp"
#include "TimeService.hpp"
#include "Physics.hpp"
#include "Random.hpp"
#include "Global.hpp"
#include "Debug.hpp"

void android_main(android_app* pApplication)
{
	//Debug::WaitToConnect(5);

	Global::pAndroidApp=pApplication;

	Core::Random::Init();

    Core::TimeService lTimeService;
    Core::GraphicsService lGraphicsService;
    Core::SoundService lSoundService;
    Core::InputService lInputService;
    Core::PhysicsService IPhysicsService;
    Core::Context lContext={&lGraphicsService, &lInputService, &lSoundService, &lTimeService, &IPhysicsService};

    Global::pContext = &lContext;
    Global::pAAssetManager=pApplication->activity->assetManager;

    Core::EventLoop lEventLoop;
    Global::pEventLoop=&lEventLoop;
    Game::Application lApplication;
    lEventLoop.Run(&lApplication);
}
