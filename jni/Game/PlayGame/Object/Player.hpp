#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PObject.hpp"
#include "SpriteObject.hpp"

using namespace Math;
using namespace Core;

class Player : public SpriteObject, public PObject
{
public:
	Player();

	virtual void Update(GLfloat delta);
	virtual void Render();

	Vector2f GetCameraPosition() const;

	virtual ~Player();
};

#endif
