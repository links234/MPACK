#ifndef ANDROIDINPUTSERVICE_HPP
#define ANDROIDINPUTSERVICE_HPP

#include "Types.hpp"
#include "Maths.hpp"

#include <android_native_app_glue.h>

#include <vector>

using namespace std;
using namespace Math;

namespace Core
{
	struct Finger;

	class AndroidInputService
	{
	public:
		AndroidInputService();
		~AndroidInputService();

		void ClearLinks();

		void Link_FUP(const Param2PtrCallbackStruct &link);
		void Link_FDOWN(const Param2PtrCallbackStruct &link);
		void Link_KEYBACK(const Param1PtrCallbackStruct &link);

		vector<Finger*> m_finger;

	public:
		bool onTouchEvent(AInputEvent* pEvent);
		bool onKeyBack();

	private:
		void UpdateFinger(GLuint id, Vector2f pos);
		void AddFinger(GLuint id, Vector2f pos);
		void DeleteFinger(GLuint id);

		vector<Param2PtrCallbackStruct> m_callbackFunc_FUP;
		vector<Param2PtrCallbackStruct> m_callbackFunc_FDOWN;

		vector<Param1PtrCallbackStruct> m_callbackFunc_KEYBACK;
	};
}
#endif
