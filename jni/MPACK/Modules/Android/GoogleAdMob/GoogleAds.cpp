#ifdef ANDROID_PLATFORM

#include "GoogleAds.hpp"
#include "Global.hpp"

JavaVM* GoogleAdsJvm;
jobject GoogleAdsJobject;

namespace MPACK
{
	namespace ADS
	{
		GoogleAds::GoogleAds(bool showAds)
		{

			mActivity = MPACK::Global::pAndroidApp->activity;
			mJvm = MPACK::Global::pAndroidApp->activity->vm;
			callMainActivityJavaFunction("sendGoogleAdsJavaVmToCpp", showAds);
		}

		void GoogleAds::removeAllAds()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("removeAllAds");
		}

		void GoogleAds::showBanner(bool top)
		{
			jboolean param = top;

			callGoogleAdsVoidJavaFunctionBool("showBanner",param);
		}

		void GoogleAds::showSmartBanner(bool top)
		{
			jboolean param = top;

			callGoogleAdsVoidJavaFunctionBool("showSmartBanner",param);
		}

		void GoogleAds::showLargeBanner(bool top)
		{
			jboolean param = top;

			callGoogleAdsVoidJavaFunctionBool("showLargeBanner",param);
		}

		void GoogleAds::hideBanner()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("hideBanner");
		}

		void GoogleAds::hideSmartBanner()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("hideSmartBanner");
		}

		void GoogleAds::hideLargeBanner()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("hideLargeBanner");
		}

		void GoogleAds::showTextImageInterstitial()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("showTextImageInterstitial");
		}

		void GoogleAds::showTextImageVideoInterstitial()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("showTextImageVideoInterstitial");
		}

		void GoogleAds::showVideoInterstitial()
		{
			callGoogleAdsVoidJavaFunctionWithoutParams("showVideoInterstitial");
		}

		bool GoogleAds::isBannerShowed()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isBannerShowed");
		}

		bool GoogleAds::isLargeBannerShowed()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isLargeBannerShowed");
		}

		bool GoogleAds::isSmartBannerShowed()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isSmartBannerShowed");
		}

		int GoogleAds::getSmartBannerWidth()
		{
			return callGoogleAdsIntJavaFunctionWithoutParams("getSmartBannerWidth");
		}

		int GoogleAds::getSmartBannerHeight()
		{
			return callGoogleAdsIntJavaFunctionWithoutParams("getSmartBannerHeight");
		}

		int GoogleAds::getBannerWidth()
		{
			return callGoogleAdsIntJavaFunctionWithoutParams("getBannerWidth");
		}

		int GoogleAds::getBannerHeight()
		{
			return callGoogleAdsIntJavaFunctionWithoutParams("getBannerHeight");
		}

		int GoogleAds::getLargeBannerWidth()
		{
			return callGoogleAdsIntJavaFunctionWithoutParams("getLargeBannerWidth");
		}

		int GoogleAds::getLargeBannerHeight()
		{
			return callGoogleAdsIntJavaFunctionWithoutParams("getLargeBannerHeight");
		}

		bool GoogleAds::isTIVInterstitialShowed()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isTIVInterstitialShowed");
		}
		bool GoogleAds::isVInterstitialShowed()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isVInterstitialShowed");
		}
		bool GoogleAds::isTIInterstitialShowed()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isTIInterstitialShowed");
		}

		bool GoogleAds::isTIVInterstitialLoaded()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isTIVInterstitialLoaded");
		}
		bool GoogleAds::isVInterstitialLoaded()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isVInterstitialLoaded");
		}
		bool GoogleAds::isTIInterstitialLoaded()
		{
			return callGoogleAdsBoolJavaFunctionWithoutParams("isTIInterstitialLoaded");
		}


		void GoogleAds::callMainActivityJavaFunction(const char *name, bool p)
		{
			JNIEnv* env = NULL;

			mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			jint res = mJvm->AttachCurrentThread(&env, NULL);

			jclass clazz = env->GetObjectClass( mActivity->clazz);

			jboolean param = p;
			jmethodID methodID = env->GetMethodID(clazz, name, "(Z)V");

			env ->CallVoidMethod(mActivity->clazz, methodID, param);

			mJvm->DetachCurrentThread();

		}

		bool GoogleAds::callGoogleAdsBoolJavaFunctionWithoutParams(const char * name)
		{
			JNIEnv* env = NULL;

			GoogleAdsJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			int res = GoogleAdsJvm->AttachCurrentThread(&env, NULL);

			jclass cls = env->GetObjectClass(GoogleAdsJobject);
			jmethodID methodID =  env ->GetMethodID(cls, name , "()Z");
			jboolean state = env ->CallIntMethod(GoogleAdsJobject, methodID);
			GoogleAdsJvm->DetachCurrentThread();
			return (bool)state;
		}

		int GoogleAds::callGoogleAdsIntJavaFunctionWithoutParams(const char * name)
		{
			JNIEnv* env = NULL;

			GoogleAdsJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			int res = GoogleAdsJvm->AttachCurrentThread(&env, NULL);

			jclass cls = env->GetObjectClass(GoogleAdsJobject);
			jmethodID methodID =  env ->GetMethodID(cls, name , "()I");
			jint state = env ->CallIntMethod(GoogleAdsJobject, methodID);
			GoogleAdsJvm->DetachCurrentThread();
			return (int)state;
		}

		void GoogleAds::callGoogleAdsVoidJavaFunctionWithoutParams(const char * name)
		{
			JNIEnv* env = NULL;

			if (GoogleAdsJvm == NULL)
			{
				LOGW("CallGoogleAdsJavaFunction GoogleAdsJvm null");
			}
			else
				LOGW("CallGoogleAdsJavaFunction GoogleAdsJvm isn't null");

			GoogleAdsJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			int res = GoogleAdsJvm->AttachCurrentThread(&env, NULL);

			if (res == 0)
				LOGI("jint is ok");
			else
				LOGI("jint is not ok %d",res);

			if (GoogleAdsJobject == NULL)
			{
				LOGI("CallGoogleAdsJavaFunction GoogleAdsJobject is null");
			}
			else
				LOGI("CallGoogleAdsJavaFunction GoogleAdsJobject isn't null");

			jclass cls = env->GetObjectClass(GoogleAdsJobject);
			jmethodID methodID =  env ->GetMethodID(cls, name , "()V");
			env ->CallVoidMethod(GoogleAdsJobject, methodID);
			GoogleAdsJvm->DetachCurrentThread();

		}


		void GoogleAds::callGoogleAdsVoidJavaFunctionBool(const char * name,jboolean boolParam)
		{
			JNIEnv* env = NULL;

			if (GoogleAdsJvm == NULL)
			{
				LOGW("CallGoogleAdsJavaFunction GoogleAdsJvm null");
			}
			else
				LOGW("CallGoogleAdsJavaFunction GoogleAdsJvm isn't null");

			GoogleAdsJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			int res = GoogleAdsJvm->AttachCurrentThread(&env, NULL);

			if (res == 0)
				LOGI("jint is ok");
			else
				LOGI("jint is not ok %d",res);

			if (GoogleAdsJobject == NULL)
			{
				LOGI("CallGoogleAdsJavaFunction GoogleAdsJobject is null");
			}
			else
				LOGI("CallGoogleAdsJavaFunction GoogleAdsJobject isn't null");

			jclass cls = env->GetObjectClass(GoogleAdsJobject);
			jmethodID methodID =  env ->GetMethodID(cls, name , "(Z)V");
			env ->CallVoidMethod(GoogleAdsJobject, methodID, boolParam);
			GoogleAdsJvm->DetachCurrentThread();

		}

	}
}



extern "C"
{
	JNIEXPORT void JNICALL Java_com_PukApp_ElasticEscape_GoogleAds_nativeGoogleAds(JNIEnv *env,jobject obj)
	{
		 int status = env->GetJavaVM( &GoogleAdsJvm);

		 if(status == 0)
		 {

			 GoogleAdsJobject = env->NewGlobalRef(obj);

			 if (obj == NULL)
			 {
				 LOGW("NativeGoogleAds : obj is null");
			 }
			 else
				 LOGW("NativeGoogleAds : obj isn't null");
			 if (GoogleAdsJobject == NULL)
			 {
				 LOGW("NativeGoogleAds : GoogleAdsJobject is null");
			 }
			 else
				 LOGW("NativeGoogleAds : GoogleAdsJobject isn't null");

		 }
		 else
			 LOGW("NativeGoogleAds : negative status !!!!!!!!!!!!!!!!!!!! %d ",status);
	}
}

#endif
