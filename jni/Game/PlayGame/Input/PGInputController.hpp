#ifndef PGINPUTCONTROLLER_HPP
#define PGINPUTCONTROLLER_HPP

#include "Types.hpp"
#include "Maths.hpp"

class PGInputController
{
public:
	PGInputController();
	virtual ~PGInputController();

	virtual void Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	virtual Math::Vector2f 	GetMovementDirection() const = 0;
	virtual Math::Vector2f 	GetShootingDirection() const = 0;
	virtual bool 			IsUserRequestingExit() = 0;

	virtual void Pause() = 0;
	virtual void Continue() = 0;

	void SetMaxAcceleration(const GLfloat &maxAcceleration);

	static PGInputController* Initialize();

protected:
	GLfloat	m_maxAcceleration;
};

#endif
