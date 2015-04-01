#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include "MPACK.hpp"

#include "Object.hpp"

class SpriteObject : virtual public Object
{
public:
	SpriteObject();
	virtual ~SpriteObject();

	virtual bool Update(GLfloat delta);
	virtual void Render();

	virtual Vector2f GetCameraPosition() const;

	virtual void SetSprite(MPACK::Graphics::Sprite *pSprite);

protected:
	MPACK::Graphics::Sprite	*m_sprite;
};

#endif
