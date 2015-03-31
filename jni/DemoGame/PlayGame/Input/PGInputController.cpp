#include "PGInputController.hpp"

#include "PGAndroidInput.hpp"
#include "PGDesktopInput.hpp"

PGInputController::PGInputController()
{
}

PGInputController::~PGInputController()
{
}

void PGInputController::SetMaxAcceleration(const GLfloat &maxAcceleration)
{
	m_maxAcceleration=maxAcceleration;
}

PGInputController* PGInputController::Initialize()
{
	PGInputController *pPGInputController=NULL;
#ifdef ANDROID_PLATFORM
	pPGInputController=new PGAndroidInput();
#elif 	defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
	pPGInputController=new PGDesktopInput();
#endif
	return pPGInputController;
}
