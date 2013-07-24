#include "MMInputController.hpp"

#include "Platform.hpp"
#include "MMAndroidInput.hpp"
#include "MMWindowsInput.hpp"

MMInputController::MMInputController()
{
}

MMInputController::~MMInputController()
{
}

void MMInputController::Link_FUP(const Param2PtrCallbackStruct &link)
{
	m_callbackFunc_FUP.push_back(link);
}

void MMInputController::Link_FDOWN(const Param2PtrCallbackStruct &link)
{
	m_callbackFunc_FDOWN.push_back(link);
}

MMInputController* MMInputController::Initialize()
{
	MMInputController *pMMInputController=NULL;
#ifdef 	ANDROID_PLATFORM
	pMMInputController=new MMAndroidInput();
#elif	defined(WINDOWS_PLATFORM)
	pMMInputController=new MMWindowsInput();
#endif
	return pMMInputController;
}
