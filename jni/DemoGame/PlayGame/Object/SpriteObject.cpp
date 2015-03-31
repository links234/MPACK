#include "SpriteObject.hpp"

using namespace MPACK;

SpriteObject::SpriteObject()
	: m_sprite(NULL)
{
}

SpriteObject::~SpriteObject()
{
}

bool SpriteObject::Update(GLfloat delta)
{
	return true;
}

void SpriteObject::Render()
{
	m_sprite->Render();
}

Vector2f SpriteObject::GetCameraPosition() const
{
	return m_sprite->m_position;
};

void SpriteObject::SetSprite(Sprite *pSprite)
{
	m_sprite=pSprite;
}
