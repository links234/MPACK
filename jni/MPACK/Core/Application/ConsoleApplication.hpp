#ifndef MPACK_CONSOLEAPPLICATION_HPP
#define MPACK_CONSOLEAPPLICATION_HPP

#include "Application.hpp"

namespace MPACK
{
	namespace Core
	{
		class ConsoleApplication : public Application
		{
		public:
			ConsoleApplication();
			virtual ~ConsoleApplication();

			virtual ReturnValue onActivate();
			virtual void onDeactivate();
			virtual ReturnValue onStep();

			virtual void onStart();
			virtual void onResume();
			virtual void onPause();
			virtual void onStop();
			virtual void onDestroy();

			virtual void onSaveState(void** pData, size_t* pSize);
			virtual void onConfigurationChanged();
			virtual void onLowMemory();

			virtual void onCreateWindow();
			virtual void onDestroyWindow();
			virtual void onGainFocus();
			virtual void onLostFocus();

			virtual int Main() = 0;
		};
	}
}
#endif
