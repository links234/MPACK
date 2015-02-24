#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "MPACK.hpp"

#include "PhysicalObject.hpp"
#include "SpriteObject.hpp"

class Projectile : public PhysicalObject, public SpriteObject
{
public:
	Projectile();
	virtual ~Projectile();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual MPACK::Math::Vector2f GetCameraPosition() const;

	virtual void SetSprite(MPACK::Graphics::Sprite *pSprite);
};

#endif
