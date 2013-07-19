#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#ifndef MMINPUTCONTROLLER_HPP
#define MMINPUTCONTROLLER_HPP

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
