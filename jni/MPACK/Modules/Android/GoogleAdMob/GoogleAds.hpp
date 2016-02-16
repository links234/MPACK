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
				void callMainActivityJavaFunction(const char *, bool p);
				void callGoogleAdsVoidJavaFunctionWithoutParams(const char * );
				void callGoogleAdsVoidJavaFunctionBool(const char *,jboolean);
				bool callGoogleAdsBoolJavaFunctionWithoutParams(const char *);
				int callGoogleAdsIntJavaFunctionWithoutParams(const char *);
				//Ordinea : int, bool, float, string

			public:

				GoogleAds(bool showAds = true);
				void showBanner(bool top);
				void showSmartBanner(bool top);
				void showLargeBanner(bool top);

				void removeAllAds();
				void hideBanner();
				void hideSmartBanner();
				void hideLargeBanner();

				void showTextImageInterstitial();
				void showTextImageVideoInterstitial();
				void showVideoInterstitial();

				bool isBannerShowed();
				bool isLargeBannerShowed();
				bool isSmartBannerShowed();

				int getBannerWidth();
				int getBannerHeight();
				int getLargeBannerWidth();
				int getLargeBannerHeight();
				int getSmartBannerWidth();
				int getSmartBannerHeight();


				 bool isTIVInterstitialShowed();
				 bool isVInterstitialShowed();
				 bool isTIInterstitialShowed();

				 bool isTIVInterstitialLoaded();
				 bool isVInterstitialLoaded();
				 bool isTIInterstitialLoaded();
		};
	}
}




#endif
#endif
