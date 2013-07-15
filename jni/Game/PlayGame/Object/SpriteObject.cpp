#include "SpriteObject.hpp"

SpriteObject::SpriteObject()
{
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::Update(GLfloat delta)
{
}

void SpriteObject::Render()
{
	m_sprite->Render();
}

void SpriteObject::SetSprite(Sprite *pSprite)
{
	m_sprite=pSprite;
}
