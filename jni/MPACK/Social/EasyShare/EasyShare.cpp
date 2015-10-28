#ifdef ANDROID_PLATFORM

#include "EasyShare.hpp"
#include "Global.hpp"

JavaVM* EasyShareJvm;
jobject EasyShareJobject;


namespace MPACK
{
	namespace SOCIAL
	{
			EasyShare::EasyShare()
			{

				mActivity = MPACK::Global::pAndroidApp->activity;
				mJvm = MPACK::Global::pAndroidApp->activity->vm;
				callMainActivityJavaFunction("sendEasyShareJavaVmToCpp");
			}


			void EasyShare::callMainActivityJavaFunction(const char *name)
					{
						JNIEnv* env = NULL;

						mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

						jint res = mJvm->AttachCurrentThread(&env, NULL);

						jclass clazz = env->GetObjectClass( mActivity->clazz);

						jmethodID methodID = env->GetMethodID(clazz, name, "()V");

						env ->CallVoidMethod(mActivity->clazz, methodID);

						mJvm->DetachCurrentThread();

					}


			void EasyShare::callEasyShareVoidJavaFunctionWithoutParams(const char * name)
			{


				JNIEnv* env = NULL;

				if (EasyShareJvm == NULL)
				{
					LOGW("CallEasyShareJavaFunction EasyShareJvm null");
				}
				else
					LOGW("CallEasyShareJavaFunction EasyShareJvm isn't null");

				EasyShareJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = EasyShareJvm->AttachCurrentThread(&env, NULL);

				if (res == 0)
					LOGI("jint is ok");
				else
					LOGI("jint is not ok %d",res);

				if (EasyShareJobject == NULL)
				{
					LOGI("CallEasyShareJavaFunction EasyShareJobject is null");
				}
				else
					LOGI("CallEasyShareJavaFunction EasyShareJobject isn't null");

				jclass cls = env->GetObjectClass(EasyShareJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()V");
				env ->CallVoidMethod(EasyShareJobject, methodID);
				EasyShareJvm->DetachCurrentThread();

			}

			void EasyShare::callEasyShareVoidJavaFunctionString(const char * name , string p1, string p2)
			{


				JNIEnv* env = NULL;

				if (EasyShareJvm == NULL)
				{
					LOGW("CallEasyShareJavaFunction EasyShareJvm null");
				}
				else
					LOGW("CallEasyShareJavaFunction EasyShareJvm isn't null");

				EasyShareJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = EasyShareJvm->AttachCurrentThread(&env, NULL);

				if (res == 0)
					LOGI("jint is ok");
				else
					LOGI("jint is not ok %d",res);

				if (EasyShareJobject == NULL)
				{
					LOGI("CallEasyShareJavaFunction EasyShareJobject is null");
				}
				else
					LOGI("CallEasyShareJavaFunction EasyShareJobject isn't null");

				jstring jp1 = env->NewStringUTF(p1.c_str());
				jstring jp2 = env->NewStringUTF(p2.c_str());

				jclass cls = env->GetObjectClass(EasyShareJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "(Ljava/lang/String;Ljava/lang/String;)V");
				env ->CallVoidMethod(EasyShareJobject, methodID,jp1,jp2);
				EasyShareJvm->DetachCurrentThread();

			}

			void EasyShare::Share(string shareSubject,string shareBody )
			{

				callEasyShareVoidJavaFunctionString("Share",shareSubject,shareBody);
			}
	}
}



extern "C"
{
	JNIEXPORT void JNICALL Java_com_PukApp_MPACK_EasyShare_nativeEasyShare(JNIEnv *env,jobject obj)
	{
		 int status = env->GetJavaVM( &EasyShareJvm);

		 if(status == 0)
		 {

			 EasyShareJobject = env->NewGlobalRef(obj);

			 if (obj == NULL)
			 {
				 LOGW("NativeGoogleAds : obj is null");
			 }
			 else
				 LOGW("NativeGoogleAds : obj isn't null");
			 if (EasyShareJobject == NULL)
			 {
				 LOGW("NativeGoogleAds : GoogleAdsJobject is null");
			 }
			 else
				 LOGW("NativeGoogleAds : GoogleAdsJobject isn't null");

		 }
		 else
			 LOGW("NativeGoogleAds : negative status ! %d ",status);
	}
}

#endif
