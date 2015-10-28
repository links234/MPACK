#ifdef ANDROID_PLATFORM

#ifndef EASYSHARE_H
#define EASYSHARE_H

#include <jni.h>
#include <android_native_app_glue.h>
#include <string>
using namespace std;

namespace MPACK
{
	namespace SOCIAL
	{
		class EasyShare
		{
			public:
				ANativeActivity* mActivity;
				JavaVM* mJvm;

			public:
				EasyShare();

			public:
				void callMainActivityJavaFunction(const char * );
				void callEasyShareVoidJavaFunctionWithoutParams(const char *);
				void callEasyShareVoidJavaFunctionString(const char *, string,string);

			public:

				void Share(string ,string);
		};
	}
}


#endif
#endif

