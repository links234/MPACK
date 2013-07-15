#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include "Object.hpp"
#include "Sprite.hpp"

class SpriteObject : public Object
{
public:
	SpriteObject();
	virtual ~SpriteObject();

	void Update(GLfloat delta);
	void Render();

	void SetSprite(Sprite *pSprite);

protected:
	Sprite	*m_sprite;
};

#endif
