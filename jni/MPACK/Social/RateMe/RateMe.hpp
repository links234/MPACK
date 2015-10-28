#ifdef ANDROID_PLATFORM

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

				const static int OK = 1;
				const static int NEVER_OPTION_TRIGGERED = 2;
				const static int ALREADY_RATED = 3;
				const static int TIME_OR_LAUNCHES_PROBLEM = 4;

			public:
				ANativeActivity* mActivity;
				JavaVM* mJvm;

			public:
				RateMe(const string,const int ,const int);

			public:
				void callMainActivityJavaFunction(const char * ,const string,const int,const int);
				void callRateMeVoidJavaFunctionWithoutParams(const char *);
				int callRateMeIntJavaFunctionWithoutParams(const char *);

			public:

				void rate();
				void rateNever();
				void rateLater();
				int check();
				void update();
				void reset();
		};
	}
}


#endif
#endif
