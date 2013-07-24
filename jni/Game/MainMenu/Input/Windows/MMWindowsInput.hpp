#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#ifndef MMWINDOWSINPUT_HPP
#define MMWINDOWSINPUT_HPP

#include "MMInputController.hpp"

class MMWindowsInput : public MMInputController
{
public:
	MMWindowsInput();
	virtual ~MMWindowsInput();

	virtual void Update(GLfloat delta);
};

#endif

#endif
