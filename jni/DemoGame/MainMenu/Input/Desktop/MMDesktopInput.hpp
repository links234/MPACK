#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MMDESKTOPINPUT_HPP
#define MMDESKTOPINPUT_HPP

#include "MMInputController.hpp"

#include "MPACK.hpp"

class MMDesktopInput : public MMInputController
{
public:
	MMDesktopInput();
	virtual ~MMDesktopInput();

	virtual void Update(GLfloat delta);

private:
	MPACK::Input::Finger	*m_pFinger;
};

#endif

#endif
