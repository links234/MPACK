#ifdef WINDOWS_PLATFORM

#ifndef PGWINDOWSINPUT_HPP
#define PGWINDOWSINPUT_HPP

#include "PGInputController.hpp"

#include "Maths.hpp"

class PGWindowsInput : public PGInputController
{
public:
	PGWindowsInput();
	virtual ~PGWindowsInput();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual void Pause();
	virtual void Continue();

	virtual Math::Vector2f 	GetMovementDirection() const;
	virtual Math::Vector2f 	GetShootingDirection() const;
	virtual bool 			IsUserRequestingExit();

protected:
	bool			m_requestExit;

	Math::Vector2f	m_movementDirection;
};

#endif

#endif
