#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MMDESKTOPINPUT_HPP
#define MMDESKTOPINPUT_HPP

#include "MMInputController.hpp"

namespace Core
{
	class Finger;
}

class MMDesktopInput : public MMInputController
{
public:
	MMDesktopInput();
	virtual ~MMDesktopInput();

	virtual void Update(GLfloat delta);

private:
	Finger	*m_pFinger;
};

#endif

#endif
