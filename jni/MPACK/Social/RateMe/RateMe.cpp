#ifdef ANDROID_PLATFORM

#include "RateMe.hpp"
#include "Global.hpp"

JavaVM* RateMeJvm;
jobject RateMeJobject;


namespace MPACK
{
	namespace SOCIAL
	{
			RateMe::RateMe(const string url,const int daysUntilPrompt,const int launchesUntilPrompt)
			{
				mActivity = MPACK::Global::pAndroidApp->activity;
				mJvm = MPACK::Global::pAndroidApp->activity->vm;
				callMainActivityJavaFunction("sendRateMeJavaVmToCpp", url,daysUntilPrompt,launchesUntilPrompt);
			}

			void RateMe::rate()
			{
				callRateMeVoidJavaFunctionWithoutParams("rate");
			}

			void RateMe::rateLater()
			{
				callRateMeVoidJavaFunctionWithoutParams("rateLater");
			}

			void RateMe::rateNever()
			{
				callRateMeVoidJavaFunctionWithoutParams("rateNever");
			}

			int RateMe::check()
			{
				return callRateMeIntJavaFunctionWithoutParams("check");
			}

			void RateMe::update()
			{
				callRateMeVoidJavaFunctionWithoutParams("update");
			}

			void RateMe::reset()
			{
				callRateMeVoidJavaFunctionWithoutParams("reset");
			}

			void RateMe::callMainActivityJavaFunction(const char *name, const string p1, const int p2, const int p3)
			{
				JNIEnv* env = NULL;

				mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				jint res = mJvm->AttachCurrentThread(&env, NULL);

				jclass clazz = env->GetObjectClass( mActivity->clazz);

				jstring jp1 = env->NewStringUTF(p1.c_str());
				jint jp2 = p2;
				jint jp3 = p3;


				jmethodID methodID = env->GetMethodID(clazz, name, "(Ljava/lang/String;II)V");

				env ->CallVoidMethod(mActivity->clazz, methodID,jp1,jp2,jp3);

				mJvm->DetachCurrentThread();
			}

			int RateMe::callRateMeIntJavaFunctionWithoutParams(const char * name)
			{

				JNIEnv* env = NULL;

				RateMeJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = RateMeJvm->AttachCurrentThread(&env, NULL);

				jclass cls = env->GetObjectClass(RateMeJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()I");
				jint state = env ->CallIntMethod(RateMeJobject, methodID);
				RateMeJvm->DetachCurrentThread();
				return (int)state;
			}

			void RateMe::callRateMeVoidJavaFunctionWithoutParams(const char * name)
			{

				JNIEnv* env = NULL;

				RateMeJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = RateMeJvm->AttachCurrentThread(&env, NULL);

				jclass cls = env->GetObjectClass(RateMeJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()V");
				env ->CallVoidMethod(RateMeJobject, methodID);
				RateMeJvm->DetachCurrentThread();
			}

	}
}



extern "C"
{
	JNIEXPORT void JNICALL Java_com_PukApp_MPACK_RateMe_nativeRateMe(JNIEnv *env,jobject obj)
	{
		 int status = env->GetJavaVM( &RateMeJvm);

		 if(status == 0)
		 {

			 RateMeJobject = env->NewGlobalRef(obj);

			 if (obj == NULL)
			 {
				 LOGW("NativeRateMe : obj is null");
			 }
			 else
				 LOGW("NativeRateMe : obj isn't null");
			 if (RateMeJobject == NULL)
			 {
				 LOGW("NativeRateMe : RateMeJobject is null");
			 }
			 else
				 LOGW("NativeRateMe : RateMeJobject isn't null");

		 }
		 else
			 LOGW("NativeRateMe : negative status ! %d ",status);
	}
}

#endif

