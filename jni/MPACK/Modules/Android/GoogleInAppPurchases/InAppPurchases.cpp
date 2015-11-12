#ifdef ANDROID_PLATFORM

#include "InAppPurchases.hpp"
#include "Global.hpp"

JavaVM* InAppPurchasesJvm;
jobject InAppPurchasesJobject;


namespace MPACK
{
	namespace SERVICES
	{
			const string InAppPurchases::SEPARATOR = "###";

			InAppPurchases::InAppPurchases()
			{
				//mIsLoaded = false;
				mActivity = MPACK::Global::pAndroidApp->activity;
				mJvm = MPACK::Global::pAndroidApp->activity->vm;
				callMainActivityJavaFunction("sendInAppPurchasesJavaVmToCpp");
			}

			void InAppPurchases::bindServices()
			{
				callInAppPurchasesVoidJavaFunctionWithoutParams("bindServices");
			}

			void InAppPurchases::destroy()
			{
				callInAppPurchasesVoidJavaFunctionWithoutParams("destroy");
			}

			void InAppPurchases::purchase(const string purchase_id, const string developerPayload)
			{
				callInAppPurchasesVoidJavaFunction2String("purchase", purchase_id, developerPayload);
			}

			void InAppPurchases::subscribe(const string purchase_id, const string developerPayload)
			{
				callInAppPurchasesVoidJavaFunction2String("subscribe", purchase_id, developerPayload);
			}

			int InAppPurchases::getServiceBindingState()
			{
				return callInAppPurchasesIntJavaFunctionWithoutParams("getServiceBindingState");
			}

			int InAppPurchases::getCurrentProcessState()
			{
				return callInAppPurchasesIntJavaFunctionWithoutParams("getCurrentProcessState");
			}

			int InAppPurchases::getCurrentProcessType()
			{
				return callInAppPurchasesIntJavaFunctionWithoutParams("getCurrentProcessType");
			}

			int InAppPurchases::getCurrentQueryProcessState()
			{
				return callInAppPurchasesIntJavaFunctionWithoutParams("getCurrentQueryProcessState");
			}

			void InAppPurchases::startQuery()
			{
				callInAppPurchasesVoidJavaFunctionWithoutParams("startQuery");
			}

			void InAppPurchases::startPriceQuery(const vector<string> & ids)
			{
				callInAppPurchasesVoidJavaFunctionVectorString("startPriceQuery", ids);
			}
			void InAppPurchases::consumeAllPurchases(const string developerPayload)
			{
				callInAppPurchasesVoidJavaFunctionString("consumeAllPurchases", developerPayload);
			}

			vector<pair<string,string> > InAppPurchases::getAllPrices()
			{
				vector<string> res;
				vector<pair<string,string> > ans;
				res = callInAppPurchasesVectorStringJavaFunctionWithoutParams("getAllPrices");

				for (int i = 0;i < res.size();i++)
				{
					string s = res[i];
					int ind = s.find(SEPARATOR);

					ans.push_back(make_pair(s.substr(0,ind), s.substr(ind + SEPARATOR.size()) ));
				}

				return ans;
			}

			vector<string> InAppPurchases::getConsumedItems()
			{
				vector<string> ans;
				ans = callInAppPurchasesVectorStringJavaFunctionWithoutParams("getConsumedItems");
				for (int i = 0 ;i < ans.size();i++)
					LOGI("%s",ans[i].c_str());
				return ans;
			}

			void InAppPurchases::callMainActivityJavaFunction(const char *name)
			{
				JNIEnv* env = NULL;

				mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				jint res = mJvm->AttachCurrentThread(&env, NULL);

				jclass clazz = env->GetObjectClass( mActivity->clazz);

				jmethodID methodID = env->GetMethodID(clazz, name, "()V");

				env ->CallVoidMethod(mActivity->clazz, methodID);

				mJvm->DetachCurrentThread();

			}


			 int InAppPurchases::callInAppPurchasesIntJavaFunctionWithoutParams(const char * name)
			 {

			 	JNIEnv* env = NULL;

			 	InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

			 	int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);

			 	jclass cls = env->GetObjectClass(InAppPurchasesJobject);
			 	jmethodID methodID =  env ->GetMethodID(cls, name , "()I");
			 	jint state = env ->CallIntMethod(InAppPurchasesJobject, methodID);
			 	InAppPurchasesJvm->DetachCurrentThread();
			 	return (int)state;
			 }

			void InAppPurchases::callInAppPurchasesVoidJavaFunctionWithoutParams(const char * name)
			{

				JNIEnv* env = NULL;

				InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);

				jclass cls = env->GetObjectClass(InAppPurchasesJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()V");
				env ->CallVoidMethod(InAppPurchasesJobject, methodID);
				InAppPurchasesJvm->DetachCurrentThread();
			}


			void InAppPurchases::callInAppPurchasesVoidJavaFunctionString(const char * name,const string p1)
			{


				JNIEnv* env = NULL;

				InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);
				jstring jp1 = env->NewStringUTF(p1.c_str());

				jclass cls = env->GetObjectClass(InAppPurchasesJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "(Ljava/lang/String;)V");
				env ->CallVoidMethod(InAppPurchasesJobject, methodID,jp1);
				InAppPurchasesJvm->DetachCurrentThread();
			}

			void InAppPurchases::callInAppPurchasesVoidJavaFunction2String(const char * name,const string p1, const string p2)
			{
				JNIEnv* env = NULL;

				InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);

				jstring jp1 = env->NewStringUTF(p1.c_str());
				jstring jp2 = env->NewStringUTF(p2.c_str());

				jclass cls = env->GetObjectClass(InAppPurchasesJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "(Ljava/lang/String;Ljava/lang/String;)V");
				env ->CallVoidMethod(InAppPurchasesJobject, methodID, jp1, jp2);
				InAppPurchasesJvm->DetachCurrentThread();
			}

			string InAppPurchases::callInAppPurchasesStringJavaFunctionWithoutParams(const char * name)
			{
				JNIEnv* env = NULL;
				InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);

				jclass cls = env->GetObjectClass(InAppPurchasesJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()Ljava/lang/String;");
				jstring returnString = (jstring) env ->CallObjectMethod(InAppPurchasesJobject, methodID);
				const char *js = env->GetStringUTFChars(returnString, NULL);
				std::string cs(js);
				env->ReleaseStringUTFChars(returnString, js);
				InAppPurchasesJvm->DetachCurrentThread();
				return cs;
			}

			void InAppPurchases::callInAppPurchasesVoidJavaFunctionVectorString(const char * name, const vector<string> & p1)
			{
				JNIEnv* env = NULL;

				InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);

				jclass cls = env->GetObjectClass(InAppPurchasesJobject);

				//Creare List

				JNIEnv* env2 = NULL;
				mJvm->GetEnv( (void **)&env2, JNI_VERSION_1_6);
				mJvm->AttachCurrentThread(&env2, NULL);
				jclass clazz = env2->FindClass("java/util/ArrayList");
				jobject obj = env2->NewObject(clazz, env2->GetMethodID(clazz, "<init>", "()V"));
				for (int i=0;i<p1.size();i++)
				{
				   jstring str = env->NewStringUTF(p1[i].c_str());
				   env2->CallBooleanMethod(obj, env2->GetMethodID(clazz, "add", "(Ljava/lang/Object;)Z"), str);
				}
				//Se afla in obj

				jmethodID methodID =  env ->GetMethodID(cls, name , "(Ljava/util/ArrayList;)V");
				env ->CallVoidMethod(InAppPurchasesJobject, methodID, obj);
				InAppPurchasesJvm->DetachCurrentThread();
			}

			static jobject obj;

			vector<string> InAppPurchases::callInAppPurchasesVectorStringJavaFunctionWithoutParams(const char * name)
			{
				JNIEnv* env = NULL;

				InAppPurchasesJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);

				int res = InAppPurchasesJvm->AttachCurrentThread(&env, NULL);

				jclass cls = env->GetObjectClass(InAppPurchasesJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()Ljava/util/ArrayList;");

				obj = env ->CallObjectMethod(InAppPurchasesJobject, methodID);

				//Creare vector<string>
				vector<string> resVector;

				JNIEnv* env2 = NULL;
				mJvm->GetEnv( (void **)&env2, JNI_VERSION_1_6);
				mJvm->AttachCurrentThread(&env2, NULL);
				jclass clazz = env2->FindClass("java/util/ArrayList");
				jint size = env2->CallIntMethod(obj, env2->GetMethodID(clazz, "size", "()I"));


				for (int i=0;i < size;i++)
				{
				   jint ind = i;
				   jstring returnString = (jstring) env2->CallObjectMethod(obj, env2->GetMethodID(clazz, "get", "(I)Ljava/lang/Object;"), ind);
				   const char *js = env->GetStringUTFChars(returnString, NULL);
				   std::string cs(js);
				   env->ReleaseStringUTFChars(returnString, js);
				   resVector.push_back(cs);
				}
				//Se afla in resVector
				InAppPurchasesJvm->DetachCurrentThread();

				return resVector;
			}

	}
}



extern "C"
{
	JNIEXPORT void JNICALL Java_com_PukApp_MPACK_InAppPurchases_nativeInAppPurchases(JNIEnv *env,jobject obj)
	{
		int status = env->GetJavaVM( &InAppPurchasesJvm);

		if(status == 0)
		{
			InAppPurchasesJobject = env->NewGlobalRef(obj);

			if (obj == NULL)
			{
				LOGW("InAppPurchases : obj is null");
			}
			else
				LOGW("InAppPurchases : obj isn't null");
			if (InAppPurchasesJobject == NULL)
			{
				LOGW("InAppPurchases : InAppPurchasesJobject is null");
			}
			else
				LOGW("InAppPurchases : InAppPurchasesJobject isn't null");
		}
		else
			LOGW("NativeInAppPurchases : negative status ! %d ",status);
	}
}

#endif
