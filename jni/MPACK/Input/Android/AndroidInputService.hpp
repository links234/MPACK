#ifdef ANDROID_PLATFORM

#ifndef MPACK_ANDROIDINPUTSERVICE_HPP
#define MPACK_ANDROIDINPUTSERVICE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Input
	{
		struct Finger;
	}
}

namespace MPACK
{
	namespace Input
	{
		class AndroidInputService
		{
		public:
			AndroidInputService();
			~AndroidInputService();

			void Update();
			void Reset();

			void ClearLinks();

			void Link_FUP(const Core::Param2PtrCallbackStruct &link);
			void Link_FDOWN(const Core::Param2PtrCallbackStruct &link);
			void Link_KEYBACK(const Core::Param1PtrCallbackStruct &link);

			void UnLink_FUP(const Core::Param2PtrCallbackStruct &link);
			void UnLink_FDOWN(const Core::Param2PtrCallbackStruct &link);
			void UnLink_KEYBACK(const Core::Param1PtrCallbackStruct &link);

			std::vector<Finger*> m_finger;

		public:
			bool onTouchEvent(AInputEvent* pEvent);
			bool onKeyBack();

		private:
			void UpdateFinger(GLuint id, Math::Vector2f pos);
			void AddFinger(GLuint id, Math::Vector2f pos);
			void DeleteFinger(GLuint id);

			std::vector<Core::Param2PtrCallbackStruct> m_callbackFunc_FUP;
			std::vector<Core::Param2PtrCallbackStruct> m_callbackFunc_FDOWN;

			std::vector<Core::Param1PtrCallbackStruct> m_callbackFunc_KEYBACK;
		};
	}
}

#endif

#endif

