#include "TimeService.hpp"

#include "Types.hpp"
#include "AndroidTimeService.hpp"
#include "WindowsTimeService.hpp"
#include "LinuxTimeService.hpp"
#include "OSXTimeService.hpp"

namespace MPACK
{
	namespace Time
	{
		TimeService::TimeService()
		{
			LOGI("Creating TimeService.");
		}

		TimeService::~TimeService()
		{
			LOGI("Destroying TimeService.");
		}

		TimeService* TimeService::Initialize()
		{
			TimeService *pTimeService = NULL;
#if defined(ANDROID_PLATFORM)
			pTimeService = (TimeService*) new AndroidTimeService();
#elif	defined(WINDOWS_PLATFORM)
			pTimeService = (TimeService*) new WindowsTimeService();
#elif	defined(LINUX_PLATFORM)
			pTimeService = (TimeService*) new LinuxTimeService();
#elif defined(OSX_PLATFORM)
			pTimeService = (TimeService*) new OSXTimeService();
#endif
			return pTimeService;
		}
	}
}
