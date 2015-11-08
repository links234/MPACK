#ifdef WINDOWS_PLATFORM

#ifndef MPACK_WINDOWSINPUTSERVICE_HPP
#define MPACK_WINDOWSINPUTSERVICE_HPP

#include "Types.hpp"
#include "MouseInterface.hpp"
#include "KeyboardInterface.hpp"

namespace MPACK
{
	namespace Input
	{
		class WindowsInputService
		{
		public:
			WindowsInputService();
			~WindowsInputService();

			void Update();
			void Reset();

			MouseInterface*		GetMouse() const;
			KeyboardInterface* 	GetKeyboard() const;

			void ClearLinks();

			void Link_FUP(const Core::Param2PtrCallbackStruct &link);
			void Link_FDOWN(const Core::Param2PtrCallbackStruct &link);
			void Link_KEYBACK(const Core::Param1PtrCallbackStruct &link);

			void UnLink_FUP(const Core::Param2PtrCallbackStruct &link);
			void UnLink_FDOWN(const Core::Param2PtrCallbackStruct &link);
			void UnLink_KEYBACK(const Core::Param1PtrCallbackStruct &link);

		private:
			void EmulateTouchscreenFinger();

			Finger				*m_pFinger;

			MouseInterface		*m_pMouse;
			KeyboardInterface	*m_pKeyboard;

			std::vector<Core::Param2PtrCallbackStruct> m_callbackFunc_FUP;
			std::vector<Core::Param2PtrCallbackStruct> m_callbackFunc_FDOWN;

			std::vector<Core::Param1PtrCallbackStruct> m_callbackFunc_KEYBACK;
		};
	}
}

#endif

#endif
