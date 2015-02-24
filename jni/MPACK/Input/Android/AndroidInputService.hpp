#ifdef ANDROID_PLATFORM

#ifndef MPACK_ANDROIDINPUTSERVICE_HPP
#define MPACK_ANDROIDINPUTSERVICE_HPP

#include "Types.hpp"

#include <vector>

namespace MPACK
{
	namespace Input
	{
		struct Finger;

		class AndroidInputService
		{
		public:
			AndroidInputService();
			~AndroidInputService();

			void Update();
			void Reset();

			void ClearLinks();

			void Link_FUP(const Param2PtrCallbackStruct &link);
			void Link_FDOWN(const Param2PtrCallbackStruct &link);
			void Link_KEYBACK(const Param1PtrCallbackStruct &link);

			void UnLink_FUP(const Param2PtrCallbackStruct &link);
			void UnLink_FDOWN(const Param2PtrCallbackStruct &link);
			void UnLink_KEYBACK(const Param1PtrCallbackStruct &link);

			std::vector<Finger*> m_finger;

		public:
			bool onTouchEvent(AInputEvent* pEvent);
			bool onKeyBack();

		private:
			void UpdateFinger(GLuint id, Math::Vector2f pos);
			void AddFinger(GLuint id, Math::Vector2f pos);
			void DeleteFinger(GLuint id);

			std::vector<Param2PtrCallbackStruct> m_callbackFunc_FUP;
			std::vector<Param2PtrCallbackStruct> m_callbackFunc_FDOWN;

			std::vector<Param1PtrCallbackStruct> m_callbackFunc_KEYBACK;
		};
	}
}

#endif

#endif

