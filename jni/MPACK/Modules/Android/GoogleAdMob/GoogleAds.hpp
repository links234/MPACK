#if defined(LINUX_PLATFORM) || defined(WINDOWS_PLATFORM)
namespace MPACK
{
	namespace ADS
	{

	}
}
#endif

#ifdef ANDROID_PLATFORM

#ifndef GOOGLEADS_H
#define GOOGLEADS_H


#include <jni.h>
#include <android_native_app_glue.h>

#include <vector>
using namespace std;


namespace MPACK
{
	namespace ADS
	{
		class GoogleAds
		{
			public:
				ANativeActivity* mActivity;
				JavaVM* mJvm;

			//	JavaVM* mGoogleAdsJvm;
			//	jobject mGoogleAdsJobject;

			public:
				void callMainActivityJavaFunction(const char *);
				void callGoogleAdsVoidJavaFunctionWithoutParams(const char * );
				void callGoogleAdsVoidJavaFunctionBool(const char *,jboolean);
				//Ordinea : int, bool, float, string

			public:

				GoogleAds();
				void showBanner(bool top);
				void showSmartBanner(bool top);
				void showLargeBanner(bool top);

				void hideBanner();
				void hideSmartBanner();
				void hideLargeBanner();


				void showTextImageInterstitial();
				void showTextImageVideoInterstitial();
				void showVideoInterstitial();

		};
	}
}




#endif
#endif
