#include "Player.hpp"

Player::Player()
{
}

void Player::Update(GLfloat delta)
{

	m_velocity+=m_acceleration*delta;
}

void Player::Render()
{

}

void Player::SetFriction(GLfloat friction)
{
	m_friction=friction;
}

void Player::SetMinFriction(GLfloat minFriction)
{
	m_minFriction=minFriction;
}

Player::~Player()
{
}
