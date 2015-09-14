#include "RateMe.hpp"
#include "Global.hpp"

JavaVM* RateMeJvm;
jobject RateMeJobject;


namespace MPACK
{
	namespace SOCIAL
	{
			RateMe::RateMe(const string appTitle, const string appPname,const int daysUntilPrompt,const int launchesUntilPrompt)
			{

				mActivity = MPACK::Global::pAndroidApp->activity;
				mJvm = MPACK::Global::pAndroidApp->activity->vm;
				callMainActivityJavaFunction("sendRateMeJavaVmToCpp",appTitle,appPname,daysUntilPrompt,launchesUntilPrompt);
			}


			void RateMe::callMainActivityJavaFunction(const char *name, const string p1, const string p2, const int p3, const int p4)
					{
						JNIEnv* env = NULL;

						mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

						jint res = mJvm->AttachCurrentThread(&env, NULL);

						jclass clazz = env->GetObjectClass( mActivity->clazz);

						jstring jp1 = env->NewStringUTF(p1.c_str());
						jstring jp2 = env->NewStringUTF(p2.c_str());
						jint jp3 = p3;
						jint jp4 = p4;


						jmethodID methodID = env->GetMethodID(clazz, name, "(Ljava/lang/String;Ljava/lang/String;II)V");

						env ->CallVoidMethod(mActivity->clazz, methodID,jp1,jp2,jp3,jp4);

						mJvm->DetachCurrentThread();

					}


			void RateMe::callRateMeVoidJavaFunctionString2Bool(const char * name,const string p1,const bool p2,const bool p3)
			{


				JNIEnv* env = NULL;

				if (RateMeJvm == NULL)
				{
					LOGW("CallEasyShareJavaFunction EasyShareJvm null");
				}
				else
					LOGW("CallEasyShareJavaFunction EasyShareJvm isn't null");

				RateMeJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = RateMeJvm->AttachCurrentThread(&env, NULL);

				if (res == 0)
					LOGI("jint is ok");
				else
					LOGI("jint is not ok %d",res);

				if (RateMeJobject == NULL)
				{
					LOGI("CallRateMeJavaFunction RateMeJobject is null");
				}
				else
					LOGI("CallRateMeJavaFunction RateMeJobject isn't null");

				jstring jp1 = env->NewStringUTF(p1.c_str());
				jboolean jp2 = p2;
				jboolean jp3 = p3;

				jclass cls = env->GetObjectClass(RateMeJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "(Ljava/lang/String;ZZ)V");
				env ->CallVoidMethod(RateMeJobject, methodID,jp1,jp2,jp3);
				RateMeJvm->DetachCurrentThread();

			}



			void RateMe::rateMeNow(const string textToShow, const bool never, const bool orientation)
			{

				callRateMeVoidJavaFunctionString2Bool("rateMeNow",textToShow, never , orientation);
			}

			void RateMe::automaticRateMe(const string textToShow, const bool never, const bool orientation)
			{
				callRateMeVoidJavaFunctionString2Bool("automaticRateMe",textToShow, never , orientation);
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

