

#ifndef INTERNETCONNECTION_HPP
#define	INTERNETCONNECTION_HPP

#ifdef ANDROID_PLATFORM
#include <jni.h>
#include <android_native_app_glue.h>
#endif

namespace MPACK
{
	namespace SERVICES
	{
		class InternetConnection
		{
			public:
				static const int CONNECTED_WIFI = 1;
				static const int CONNECTED_MOBILE = 2;
				static const int DISCONNECTED = 3;

			#ifdef ANDROID_PLATFORM
			private:
				ANativeActivity* mActivity;
				JavaVM* mJvm;
			#endif

			public:
				InternetConnection();
				int IsConnected();

			#ifdef ANDROID_PLATFORM
			private :
				void callMainActivityJavaFunction(const char * );
				int callInternetConnectionIntJavaFunctionWithoutParams(const char *);
			#endif
		};
	}
}

#endif

