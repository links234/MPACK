#ifdef ANDROID_PLATFORM

#include "GoogleAds.hpp"
#include "Global.hpp"

JavaVM* GoogleAdsJvm;
jobject GoogleAdsJobject;

namespace MPACK
{
	namespace ADS
	{
		GoogleAds::GoogleAds()
		{

			mActivity = MPACK::Global::pAndroidApp->activity;
			mJvm = MPACK::Global::pAndroidApp->activity->vm;
			callMainActivityJavaFunction("sendGoogleAdsJavaVmToCpp");

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

		void GoogleAds::callMainActivityJavaFunction(const char *name )
		{
			JNIEnv* env = NULL;

			mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			jint res = mJvm->AttachCurrentThread(&env, NULL);

			jclass clazz = env->GetObjectClass( mActivity->clazz);

			jmethodID methodID = env->GetMethodID(clazz, name, "()V");

			env ->CallVoidMethod(mActivity->clazz, methodID);

			mJvm->DetachCurrentThread();

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
	JNIEXPORT void JNICALL Java_com_PukApp_MPACK_GoogleAds_nativeGoogleAds(JNIEnv *env,jobject obj)
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
