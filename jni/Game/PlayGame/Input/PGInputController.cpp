#include "PGInputController.hpp"

#include "Platform.hpp"
#include "PGAndroidInput.hpp"
#include "PGWindowsInput.hpp"

PGInputController::PGInputController()
{
}

PGInputController::~PGInputController()
{
}

PGInputController* PGInputController::Initialize()
{
	PGInputController *pPGInputController=NULL;
#ifdef ANDROID_PLATFORM
	pPGInputController=new PGAndroidInput();
#elif 	defined(WINDOWS_PLATFORM)
	pPGInputController=new PGWindowsInput();
#endif
	return pPGInputController;
}
