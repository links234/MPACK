#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef WSWINDOWSINPUT_HPP
#define WSWINDOWSINPUT_HPP

#include "MPACK.hpp"

#include "WSInputController.hpp"

class WSDesktopInput : public WSInputController
{
public:
										WSDesktopInput();
	virtual 							~WSDesktopInput();

	virtual void						Update(GLfloat delta);
	virtual void 						Render();

	virtual void 						Pause();
	virtual void 						Continue();

	virtual MPACK::Math::Vector2f 		GetMovementDirection() const;
	virtual MPACK::Math::Vector2f 		GetShootingDirection() const;
	virtual bool 						IsUserRequestingExit();
	virtual bool 						GetLeftMouseButtonUp();
	virtual bool						GetLeftMouseButtonPressed();
	virtual MPACK::Math::Vector2f		GetMousePosition();

protected:
	bool								m_requestExit;
	bool								m_userPressedLeftClick;
	bool								m_userIsPressingLeftClick;


	MPACK::Math::Vector2f	m_movementDirection;
};

#endif

#endif
