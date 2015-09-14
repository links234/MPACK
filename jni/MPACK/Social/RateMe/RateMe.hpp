#ifndef	RATEME_H
#define RATEME_H

#include <jni.h>
#include <android_native_app_glue.h>
#include <string>
using namespace std;

namespace MPACK
{
	namespace SOCIAL
	{
		class RateMe
		{
			public:

				const static bool VerticalOrientation = true;
				const static bool HorizontalOrientation = false;
				const static bool NeverButtonOn = true;
				const static bool NeverButtonOff = false;

			public:
				ANativeActivity* mActivity;
				JavaVM* mJvm;

			public:
				RateMe(const string ,const string ,const int ,const int);

			public:
				void callMainActivityJavaFunction(const char * ,const string,const string,const int,const int);
				void callRateMeVoidJavaFunctionString2Bool(const char *,const string , const bool,const bool);


			public:

				void rateMeNow(const string , const bool , const bool);
				void automaticRateMe(const string, const bool,const bool);
		};
	}
}


#endif
