#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef PGWINDOWSINPUT_HPP
#define PGWINDOWSINPUT_HPP

#include "MPACK.hpp"

#include "PGInputController.hpp"

class PGDesktopInput : public PGInputController
{
public:
	PGDesktopInput();
	virtual ~PGDesktopInput();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual void Pause();
	virtual void Continue();

	virtual MPACK::Math::Vector2f 	GetMovementDirection() const;
	virtual MPACK::Math::Vector2f 	GetShootingDirection() const;
	virtual bool 			IsUserRequestingExit();

protected:
	bool			m_requestExit;

	MPACK::Math::Vector2f	m_movementDirection;
};

#endif

#endif
