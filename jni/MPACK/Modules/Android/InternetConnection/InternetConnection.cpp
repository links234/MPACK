#include "InternetConnection.hpp"
#include "Debug.hpp"
#include "Global.hpp"

#ifdef ANDROID_PLATFORM
JavaVM* InternetConnectionJvm;
jobject InternetConnectionJobject;
#endif


namespace MPACK
{
	namespace SERVICES
	{
		InternetConnection::InternetConnection()
		{
			#ifdef ANDROID_PLATFORM
			mActivity = MPACK::Global::pAndroidApp->activity;
			mJvm = MPACK::Global::pAndroidApp->activity->vm;
			callMainActivityJavaFunction("sendInternetConnectionJavaVmToCpp");
			#endif
		}

		int InternetConnection::IsConnected()
		{
			#ifdef ANDROID_PLATFORM
			return callInternetConnectionIntJavaFunctionWithoutParams("IsConnected");
			#endif
		}

		#ifdef ANDROID_PLATFORM
		int InternetConnection::callInternetConnectionIntJavaFunctionWithoutParams(const char *name)
		{
			JNIEnv* env = NULL;
			InternetConnectionJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
			int res = InternetConnectionJvm->AttachCurrentThread(&env, NULL);
			jclass cls = env->GetObjectClass(InternetConnectionJobject);
			jmethodID methodID =  env ->GetMethodID(cls, name , "()I");
			jint state = env ->CallIntMethod(InternetConnectionJobject, methodID);
			InternetConnectionJvm->DetachCurrentThread();
			return (int)state;

		}

		void InternetConnection::callMainActivityJavaFunction(const char *name )
		{
			JNIEnv* env = NULL;

			mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			jint res = mJvm->AttachCurrentThread(&env, NULL);

			jclass clazz = env->GetObjectClass( mActivity->clazz);

			jmethodID methodID = env->GetMethodID(clazz, name, "()V");

			env ->CallVoidMethod(mActivity->clazz, methodID);

			mJvm->DetachCurrentThread();
		}
		#endif
	}
}

#ifdef ANDROID_PLATFORM
extern "C"
{
	JNIEXPORT void JNICALL Java_com_PukApp_ElasticEscape_InternetConnection_nativeInternetConnection(JNIEnv *env,jobject obj)
	{
		 int status = env->GetJavaVM( &InternetConnectionJvm);

		 if(status == 0)
		 {

			 InternetConnectionJobject = env->NewGlobalRef(obj);

			 if (obj == NULL)
			 {
				 LOGW("NativeInternetConnection : obj is null");
			 }
			 else
				 LOGI("NativeInternetConnection : obj isn't null");
			 if (InternetConnectionJobject == NULL)
			 {
				 LOGW("NativeInternetConnection : InternetConnectionJobject is null");
			 }
			 else
				 LOGI("NativeInternetConnection : InternetConnectionJobject isn't null");

		 }
		 else
			 LOGI("NativeInternetConnection : negative status !!!!!!!!!!!!!!!!!!!! %d ",status);
	}
}
#endif

