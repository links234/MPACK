#include "Platform.hpp"

#ifdef WINDOWS_PLATFORM

#ifndef PGWINDOWSINPUT_HPP
#define PGWINDOWSINPUT_HPP

#include "PGInputController.hpp"

class PGWindowsInput : public PGInputController
{
public:
	PGWindowsInput();
	virtual ~PGWindowsInput();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f 	GetMovementDirection() const;
	virtual Vector2f 	GetShootingDirection() const;
	virtual bool 		IsUserRequestingExit() const;
};

#endif

#endif
