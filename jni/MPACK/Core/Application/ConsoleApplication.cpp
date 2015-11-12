#include "ConsoleApplication.hpp"

namespace MPACK
{
	namespace Core
	{
		ConsoleApplication::ConsoleApplication()
		{
			m_applicationType = APP_CONSOLE;
		}

		ConsoleApplication::~ConsoleApplication()
		{
		}

		ReturnValue ConsoleApplication::onActivate()
		{
			return RETURN_VALUE_KO;
		}

		void ConsoleApplication::onDeactivate()
		{
		}

		ReturnValue ConsoleApplication::onStep()
		{
			return RETURN_VALUE_KO;
		}

		void ConsoleApplication::onStart()
		{
		}

		void ConsoleApplication::onResume()
		{
		}

		void ConsoleApplication::onPause()
		{
		}

		void ConsoleApplication::onStop()
		{
		}

		void ConsoleApplication::onDestroy()
		{
		}

		void ConsoleApplication::onSaveState(void** pData, size_t* pSize)
		{
		}

		void ConsoleApplication::onConfigurationChanged()
		{
		}

		void ConsoleApplication::onLowMemory()
		{
		}

		void ConsoleApplication::onCreateWindow()
		{
		}

		void ConsoleApplication::onDestroyWindow()
		{
		}

		void ConsoleApplication::onGainFocus()
		{
		}

		void ConsoleApplication::onLostFocus()
		{
		}
	}
}
