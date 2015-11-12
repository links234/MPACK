#ifndef MPACK_ANDROIDAPPLICATION_HPP
#define MPACK_ANDROIDAPPLICATION_HPP

#include "Application.hpp"

namespace MPACK
{
	namespace Core
	{
		class AndroidApplication : public Application
		{
		public:
			AndroidApplication();
			virtual ~AndroidApplication();

			virtual ReturnValue onActivate() = 0;
			virtual void onDeactivate() = 0;
			virtual ReturnValue onStep() = 0;

			virtual void onStart() = 0;
			virtual void onResume() = 0;
			virtual void onPause() = 0;
			virtual void onStop() = 0;
			virtual void onDestroy() = 0;

			virtual void onSaveState(void** pData, size_t* pSize) = 0;
			virtual void onConfigurationChanged() = 0;
			virtual void onLowMemory() = 0;

			virtual void onCreateWindow() = 0;
			virtual void onDestroyWindow() = 0;
			virtual void onGainFocus() = 0;
			virtual void onLostFocus() = 0;

			virtual int Main();
		};
	}
}
#endif
