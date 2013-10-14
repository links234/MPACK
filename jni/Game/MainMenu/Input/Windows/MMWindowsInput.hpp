#ifdef WINDOWS_PLATFORM

#ifndef MMWINDOWSINPUT_HPP
#define MMWINDOWSINPUT_HPP

#include "MMInputController.hpp"

namespace Core
{
	class Finger;
}

class MMWindowsInput : public MMInputController
{
public:
	MMWindowsInput();
	virtual ~MMWindowsInput();

	virtual void Update(GLfloat delta);

private:
	Finger	*m_pFinger;
};

#endif

#endif
