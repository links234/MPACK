#include "Player.hpp"

Player::Player()
{
}

void Player::Update(GLfloat delta)
{
	m_angle=m_linearVelocity.Angle();
	m_sprite->m_position=m_position;
	m_sprite->SetAngle(m_angle);
}

void Player::Render()
{
	SpriteObject::Render();
}

Vector2f Player::GetCameraPosition() const
{
	return m_sprite->m_position;
}

Player::~Player()
{
}
