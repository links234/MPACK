#ifndef WSINPUTCONTROLLER_HPP
#define WSINPUTCONTROLLER_HPP

#include "MPACK.hpp"

class WSInputController
{
public:
											WSInputController();
	virtual 								~WSInputController();

	virtual void 							Update(GLfloat delta) = 0;
	virtual void 							Render() = 0;

	virtual MPACK::Math::Vector2f 			GetMovementDirection() const = 0;
	virtual MPACK::Math::Vector2f 			GetShootingDirection() const = 0;
	virtual bool 							IsUserRequestingExit() = 0;
	virtual bool							GetLeftMouseButtonUp() = 0;
	virtual bool							GetLeftMouseButtonPressed() = 0;
	virtual MPACK::Math::Vector2f			GetMousePosition() = 0;

	virtual void							Pause() = 0;
	virtual void							Continue() = 0;

	void 									SetMaxAcceleration(const GLfloat &maxAcceleration);

	static WSInputController* 				Initialize();

protected:
	GLfloat	m_maxAcceleration;
};

#endif
