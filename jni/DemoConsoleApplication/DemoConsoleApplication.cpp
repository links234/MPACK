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

		MPACK::Core::Console::SetBGColor(MPACK::Core::Console::BG_RED);
		MPACK::Core::Console::SetFGColor(MPACK::Core::Console::FG_BLUE);

		LOGD("Demo::ConsoleApplication is working!!!");

		return 0;
	}
}
