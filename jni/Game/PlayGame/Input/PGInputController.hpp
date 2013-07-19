#ifndef PGINPUTCONTROLLER_HPP
#define PGINPUTCONTROLLER_HPP

#include "Types.hpp"
#include "Maths.hpp"

using namespace Math;

class PGInputController
{
public:
	PGInputController();
	virtual ~PGInputController();

	virtual void Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	virtual Vector2f 	GetMovementDirection() const = 0;
	virtual Vector2f 	GetShootingDirection() const = 0;
	virtual bool 		IsUserRequestingExit() const = 0;

	static PGInputController* InitializeController();
};

#endif
