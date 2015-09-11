#include "WSInputController.hpp"

#include "WSDesktopInput.hpp"

WSInputController::WSInputController()
{
}

WSInputController::~WSInputController()
{
}

void WSInputController::SetMaxAcceleration(const GLfloat &maxAcceleration)
{
	m_maxAcceleration=maxAcceleration;
}

WSInputController* WSInputController::Initialize()
{
	WSInputController *pWSInputController=NULL;
#if	defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
	pWSInputController=new WSDesktopInput();
#endif
	return pWSInputController;
}
