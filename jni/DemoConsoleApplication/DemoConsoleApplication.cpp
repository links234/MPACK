#include "DemoConsoleApplication.hpp"

namespace Demo
{
	ConsoleApplication::ConsoleApplication()
	{
	}

	ConsoleApplication::~ConsoleApplication()
	{
	}

	int ConsoleApplication::Main()
	{
		LOGI("Demo::ConsoleApplication is working!!!");
		LOGD("Demo::ConsoleApplication has a bug!");
		LOGW("Demo::ConsoleApplication this should not be happening, falling back to older version!");
		LOGE("Demo::ConsoleApplication error, could not recover");
		return 0;
	}
}
