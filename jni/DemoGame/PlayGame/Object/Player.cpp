#include "Player.hpp"

using namespace MPACK;
using namespace MPACK::Core;
using namespace MPACK::Math;
using namespace MPACK::Physics;

Player::Player(MPACK::Physics::World *world)
	: PhysicalObject(world)
{
	m_thisPointer = ToVoidPointer(this);
}

Player::~Player()
{
	LOGD("TEST");
}

bool Player::Update(GLfloat delta)
{
	m_sprite->m_position=m_body->GetPosition();
	m_sprite->SetAngle(m_body->GetOrientation()+270.0f);
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

	PolygonShape *poly = new PolygonShape;
	poly->SetAsBox(m_sprite->GetWidth()*0.5f,m_sprite->GetHeight()*0.5f);

	if(m_shape)
	{
		delete m_shape;
	}
	if(m_body)
	{
		m_world->Destroy(m_body);
	}

	m_shape = poly;
	m_body = m_world->Add(m_shape,0,0);

	m_body->SetOrientation(0.0f);
	m_body->LockOrientation();

	m_body->userData = (void*)&m_thisPointer;
}

void Player::Shoot(Vector2f direction)
{

}
