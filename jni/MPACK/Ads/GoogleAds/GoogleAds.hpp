#ifndef GOOGLEADS.H
#define GOOGLEADS.H

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
				void callMainActivityJavaFunction(char * , char *);
				void getGoogleAdsJavaReff();

				void callGoogleAdsJavaFunction(char * , char *);

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
