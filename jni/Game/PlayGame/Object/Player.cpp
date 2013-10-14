#include "Player.hpp"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Update(GLfloat delta)
{
	m_angle=m_linearVelocity.Angle();
	m_sprite->m_position=m_position;
	m_sprite->SetAngle(m_angle);
	return true;
}

void Player::Render()
{
	SpriteObject::Render();
	PhysicalObject::Render();
}

Vector2f Player::GetCameraPosition() const
{
	return m_sprite->m_position;
}

void Player::SetSprite(Sprite *pSprite)
{
	m_sprite=pSprite;
	PPoly *poly=(PPoly*)(m_shape);
	poly->SetAsBox(m_sprite->GetWidth()*0.5f,m_sprite->GetHeight()*0.5f);
}

void Player::Shoot(Vector2f direction)
{

}
