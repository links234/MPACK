#include "Encryptor.hpp"
#include "Global.hpp"
#include <string>

#ifdef ANDROID_PLATFORM
#include <jni.h>
#include <android_native_app_glue.h>
#endif

using namespace std;

namespace MPACK
{
	namespace Encryptor
	{
	#ifdef ANDROID_PLATFORM
		static ANativeActivity* mActivity = 0;
		static JavaVM* mJvm = 0;
	#endif

		void Init()
		{
	#ifdef ANDROID_PLATFORM
			if (!mJvm)
			{
				mActivity = MPACK::Global::pAndroidApp->activity;
				mJvm = MPACK::Global::pAndroidApp->activity->vm;
			}
	#endif
		}

		string callStringMethodString(const char * name, const string p1)
				{
			#ifdef ANDROID_PLATFORM
					JNIEnv* env = NULL;
					mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
					jint res = mJvm->AttachCurrentThread(&env, NULL);
					jclass clazz = env->GetObjectClass( mActivity->clazz);
					jmethodID methodID = env->GetMethodID(clazz, name, "(Ljava/lang/String;)Ljava/lang/String;");
					jstring param1 = env->NewStringUTF(p1.c_str());
					jstring returnString = (jstring) env ->CallObjectMethod(mActivity->clazz, methodID, param1);
					const char *js = env->GetStringUTFChars(returnString, NULL);
					std::string cs(js);
					env->ReleaseStringUTFChars(returnString, js);
					mJvm->DetachCurrentThread();
					return cs;
			#else
					return "";
			#endif
				}

#ifdef ANDROID_PLATFORM
		static jbyteArray outputArray;
#endif

		std::vector<unsigned char> callVectoryByteJavaFunctionVectorByte(const char *name , std::vector<unsigned char> p1)
		{
#ifdef ANDROID_PLATFORM
			JNIEnv* env = NULL;
			mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
			jint res = mJvm->AttachCurrentThread(&env, NULL);
			jclass clazz = env->GetObjectClass( mActivity->clazz);

			//Create data
			char *data = new char[p1.size()];
			for (int i = 0; i < p1.size(); i++)
				data[i] = p1[i];
			int data_size = p1.size();

			//Creare Vector of bytes

			jbyteArray inputArray = env->NewByteArray(data_size);
			void *temp = env->GetPrimitiveArrayCritical( (jarray)inputArray, 0);
			memcpy(temp, data, data_size);
			env->ReleasePrimitiveArrayCritical(inputArray, temp, 0);

			jmethodID methodID = env->GetMethodID(clazz, name, "([B)[B");
			outputArray = (jbyteArray)(env)->CallObjectMethod(mActivity->clazz, methodID, inputArray);
			env->DeleteLocalRef(inputArray);
			int dataOutputSize = env->GetArrayLength(outputArray);
			jbyte* dataOutput = env->GetByteArrayElements(outputArray, NULL);

			//Transform rezultatul
			vector<unsigned char> result;

			for (int i = 0;i < dataOutputSize; i++)
				result.push_back((unsigned char)dataOutput[i]);

			if (dataOutput != NULL)
				env->ReleaseByteArrayElements(outputArray, dataOutput, JNI_ABORT);

			mJvm->DetachCurrentThread();

			return result;
#else
			std::vector<unsigned char> result;
			return result;
#endif
		}

		std::vector<unsigned char> Encrypt(std::vector<unsigned char> param)
		{
			Init();
			return callVectoryByteJavaFunctionVectorByte("encrypt", param);
		}



		std::vector<unsigned char> Decrypt(std::vector<unsigned char> param)
		{
			Init();
			return callVectoryByteJavaFunctionVectorByte("decrypt", param);
		}

		void Destroy()
		{
	#ifdef ANDROID_PLATFORM
				mActivity = 0;
				mJvm = 0;
	#endif
		}


	}
}
