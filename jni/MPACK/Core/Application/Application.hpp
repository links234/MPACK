#ifndef MPACK_APPLICATION_HPP
#define MPACK_APPLICATION_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Core
	{
		enum ApplicationType {APP_BLANK, APP_ANDROID, APP_CONSOLE};

		class Application
		{
		public:
			Application();
			virtual ~Application();

			ApplicationType GetType() const;

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

			virtual int Main() = 0;

		protected:
			ApplicationType m_applicationType;
		};
	}
}
#endif
