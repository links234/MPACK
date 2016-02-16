#include "Keyboard.hpp"
#include "Global.hpp"
#include "MPACK.hpp"

#ifdef ANDROID_PLATFORM
#include <jni.h>
#include <android_native_app_glue.h>
JavaVM* KeyboardJvm;
jobject KeyboardJobject;
#endif

using namespace std;


namespace MPACK
{
	namespace SERVICES
	{
		namespace Keyboard
		{
#ifdef ANDROID_PLATFORM
			bool mEnterState = false;
			string mText;
			ANativeActivity* mActivity;
			JavaVM* mJvm;
			int hasToShow = false;

			void callMainActivityJavaFunction(const char *name, const int p1)
			{
				JNIEnv* env = NULL;
				mJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
				jint res = mJvm->AttachCurrentThread(&env, NULL);
				jclass clazz = env->GetObjectClass( mActivity->clazz);
				jmethodID methodID = env->GetMethodID(clazz, name, "(I)V");
				env ->CallVoidMethod(mActivity->clazz, methodID, (jint) p1);
				mJvm->DetachCurrentThread();
			}

			void callKeyboardVoidMethodBool(const char *name,const bool p1)
			{
				JNIEnv* env = NULL;
				KeyboardJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
				int res = KeyboardJvm->AttachCurrentThread(&env, NULL);
				jclass cls = env->GetObjectClass(KeyboardJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "(Z)V");
				env ->CallVoidMethod(KeyboardJobject, methodID, p1);
				KeyboardJvm->DetachCurrentThread();
			}

			void callKeyboardVoidMethodString(const char *name, const string p1)
			{
				JNIEnv* env = NULL;
				KeyboardJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
				int res = KeyboardJvm->AttachCurrentThread(&env, NULL);
				jclass cls = env->GetObjectClass(KeyboardJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "(Ljava/lang/String;)V");
				jstring param1 = env->NewStringUTF(p1.c_str());
				env ->CallVoidMethod(KeyboardJobject, methodID, param1);
				KeyboardJvm->DetachCurrentThread();
			}

			bool callKeyboardBoolMethodNoParams(const char *name)
			{
				JNIEnv* env = NULL;
				KeyboardJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
				int res = KeyboardJvm->AttachCurrentThread(&env, NULL);
				jclass cls = env->GetObjectClass(KeyboardJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()Z");
				bool result = (bool) env ->CallBooleanMethod(KeyboardJobject, methodID);
				KeyboardJvm->DetachCurrentThread();
				return result;
			}

			string callKeyboardStringMethodNoParams(const char *name)
			{
				JNIEnv* env = NULL;
				KeyboardJvm->GetEnv( (void **)&env, JNI_VERSION_1_6);
				int res = KeyboardJvm->AttachCurrentThread(&env, NULL);
				jclass cls = env->GetObjectClass(KeyboardJobject);
				jmethodID methodID =  env ->GetMethodID(cls, name , "()Ljava/lang/String;");
				jstring returnString = (jstring) env ->CallObjectMethod(KeyboardJobject, methodID);
				const char *js = env->GetStringUTFChars(returnString, NULL);
				std::string cs(js);
				env->ReleaseStringUTFChars(returnString, js);
				KeyboardJvm->DetachCurrentThread();
				return cs;
			}

			void Init(int charLimit)
			{
				hasToShow = false;
				mActivity = MPACK::Global::pAndroidApp->activity;
				mJvm = MPACK::Global::pAndroidApp->activity->vm;
				callMainActivityJavaFunction("sendKeyboardJavaVmToCpp", charLimit);
			}


			void Show()
			{
				hasToShow = true;
				callKeyboardVoidMethodBool("changeState", true);
			}

			void Hide()
			{
				callKeyboardVoidMethodBool("changeState", false);
			}


			string GetText()
			{
				return callKeyboardStringMethodNoParams("getText");
			}

			void SetText(const string newText)
			{
				callKeyboardVoidMethodString("setText", newText);
			}

			bool IsVisible()
			{
				bool ans = callKeyboardBoolMethodNoParams("isVisible");
				if (ans  == true) hasToShow = false;
				return ans;
			}
#endif
		}
	}
}

#ifdef ANDROID_PLATFORM

extern "C"
{
	JNIEXPORT void JNICALL Java_com_PukApp_ElasticEscape_Keyboard_nativeKeyboard(JNIEnv *env,jobject obj)
	{
		 int status = env->GetJavaVM( &KeyboardJvm);

		 if(status == 0)
		 {

			 KeyboardJobject = env->NewGlobalRef(obj);

			 if (obj == NULL)
			 {
				 LOGW("NativeKeyboard : obj is null");
			 }
			 else
				 LOGW("NativeKeyboard : obj isn't null");
			 if (KeyboardJobject == NULL)
			 {
				 LOGW("NativeKeyboard : KeyboardJobject is null");
			 }
			 else
				 LOGW("NativeKeyboard : KeyboardJobject isn't null");

		 }
		 else
			 LOGW("NativeKeyboard : negative status ! %d ",status);
	}

}


#endif
