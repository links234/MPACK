#include "GoogleAds.hpp"
#include "Global.hpp"

static JavaVM* GoogleAdsJvm;
static jobject GoogleAdsJobject;


namespace MPACK
{
	namespace ADS
	{
		GoogleAds::GoogleAds()
		{

			mActivity = MPACK::Global::pAndroidApp->activity;
			mJvm = MPACK::Global::pAndroidApp->activity->vm;
			callMainActivityJavaFunction("sendGoogleAdsJavaVmToCpp","()V");

		}



		void GoogleAds::getGoogleAdsJavaReff()
		{
			//mGoogleAdsJvm = GoogleAdsJvm;
			//mGoogleAdsJobject = GoogleAdsJobject;
		}


		void GoogleAds::showBanner()
		{
			callGoogleAdsJavaFunction("showBanner","()V");
		}

		void GoogleAds::showSmartBanner()
		{
			callGoogleAdsJavaFunction("showSmartBanner","()V");
		}

		void GoogleAds::showLargeBanner()
		{
			callGoogleAdsJavaFunction("showLargeBanner","()V");
		}

		void GoogleAds::hideBanner()
		{
			callGoogleAdsJavaFunction("hideBanner","()V");
		}

		void GoogleAds::hideSmartBanner()
		{
			callGoogleAdsJavaFunction("hideSmartBanner","()V");
		}

		void GoogleAds::hideLargeBanner()
		{
			callGoogleAdsJavaFunction("hideLargeBanner","()V");
		}

		void GoogleAds::showTextImageInterstitial()
		{
			callGoogleAdsJavaFunction("showTextImageInterstitial","()V");
		}

		void GoogleAds::showTextImageVideoInterstitial()
		{
			callGoogleAdsJavaFunction("showTextImageVideoInterstitial","()V");
		}

		void GoogleAds::showVideoInterstitial()
		{
			callGoogleAdsJavaFunction("showVideoInterstitial","()V");
		}

		void GoogleAds::callMainActivityJavaFunction(char *name , char *param)
		{
			JNIEnv* env = NULL;

			mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			jint res = mJvm->AttachCurrentThread(&env, NULL);

			jclass clazz = env->GetObjectClass( mActivity->clazz);

			jmethodID methodID = env->GetMethodID(clazz, name, param);

			env ->CallVoidMethod(mActivity->clazz, methodID);

			mJvm->DetachCurrentThread();

		}


		void GoogleAds::callGoogleAdsJavaFunction(char * name, char * param)
		{


			JNIEnv* env = NULL;



			if (GoogleAdsJvm == NULL)
			{
				LOGW("CallGoogleAdsJavaFunction GoogleAdsJvm null");
			}
			else
				LOGW("CallGoogleAdsJavaFunction GoogleAdsJvm isn't null");

			GoogleAdsJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			LOGI("CallGoogleAdsJavaFunction 2");

			int res = GoogleAdsJvm->AttachCurrentThread(&env, NULL);

			if (res == 0)
				LOGI("jint is ok");
			else
				LOGI("jint is not ok %d",res);


			LOGI("CallGoogleAdsJavaFunction 3");

			if (GoogleAdsJobject == NULL)
			{
				LOGI("CallGoogleAdsJavaFunction GoogleAdsJobject is null");
			}
			else
				LOGI("CallGoogleAdsJavaFunction GoogleAdsJobject isn't null");

			jclass cls = env->GetObjectClass(GoogleAdsJobject);

			LOGI("CallGoogleAdsJavaFunction 4");

			jmethodID methodID =  env ->GetMethodID(cls, name , param);

			LOGI("CallGoogleAdsJavaFunction 5");

			env ->CallVoidMethod(GoogleAdsJobject, methodID);

			LOGI("CallGoogleAdsJavaFunction 6");

			GoogleAdsJvm->DetachCurrentThread();

			LOGI("CallGoogleAdsJavaFunction 7");
		}

	}
}



extern "C"
{
	JNIEXPORT void JNICALL Java_com_mpack_Framework_GoogleAds_nativeGoogleAds(JNIEnv *env,jobject obj)
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

