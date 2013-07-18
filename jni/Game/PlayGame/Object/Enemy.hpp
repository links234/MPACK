#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "SpriteObject.hpp"
#include "PhysicalObject.hpp"

class Enemy : public SpriteObject, public PhysicalObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;
};

#endif
