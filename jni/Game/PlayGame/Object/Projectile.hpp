#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "PhysicalObject.hpp"
#include "SpriteObject.hpp"

class Projectile : public PhysicalObject, public SpriteObject
{
public:
	Projectile();
	virtual ~Projectile();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;

	virtual void SetSprite(Sprite *pSprite);
};

#endif
