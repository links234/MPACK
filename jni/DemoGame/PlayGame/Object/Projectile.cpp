#include "Projectile.hpp"

using namespace MPACK;

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

bool Projectile::Update(GLfloat delta)
{
	SpriteObject::Update(delta);
	PhysicalObject::Update(delta);
	return true;
}

void Projectile::Render()
{
	SpriteObject::Render();
	PhysicalObject::Render();
}

Vector2f Projectile::GetCameraPosition() const
{
	return m_sprite->m_position;
}

void Projectile::SetSprite(Sprite *pSprite)
{
	m_sprite=pSprite;
}
