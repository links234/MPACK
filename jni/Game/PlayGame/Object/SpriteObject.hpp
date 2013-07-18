#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include "Object.hpp"
#include "Sprite.hpp"

class SpriteObject : virtual public Object
{
public:
	SpriteObject();
	virtual ~SpriteObject();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;

	virtual void SetSprite(Sprite *pSprite);

protected:
	Sprite	*m_sprite;
};

#endif
