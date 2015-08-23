#ifdef ANDROID_PLATFORM

#ifndef GOOGLEADS_H
#define GOOGLEADS_H

#include <jni.h>
#include <android_native_app_glue.h>



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
				void callMainActivityJavaFunction(const char * ,const char *);
				void getGoogleAdsJavaReff();
				void callGoogleAdsJavaFunction(const char * , const char *);

			public:
				GoogleAds();

				void showBanner();
				void showSmartBanner();
				void showLargeBanner();

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
