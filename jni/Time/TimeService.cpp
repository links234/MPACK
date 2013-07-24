#include "TimeService.hpp"

#include "Platform.hpp"
#include "Types.hpp"
#include "AndroidTimeService.hpp"
#include "WindowsTimeService.hpp"

namespace Core
{
	TimeService::TimeService()
	{
	}

	TimeService::~TimeService()
	{
	}

	TimeService* TimeService::Initialize()
	{
		TimeService *pTimeService = NULL;
#ifdef ANDROID_PLATFORM
		pTimeService = (TimeService*) new AndroidTimeService();
#elif	defined(WINDOWS_PLATFORM)
		pTimeService = (TimeService*) new WindowsTimeService();
#endif
		return pTimeService;
	}
}
