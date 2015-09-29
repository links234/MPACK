#include "WSRockObject.hpp"
#include <cassert>

using namespace MPACK;
using namespace MPACK::Physics;
using namespace MPACK::Graphics;
using namespace MPACK::Math;

WSRockObject::WSRockObject(World * world)
	: WSPhysicalObject(world)
{

}

WSRockObject::~WSRockObject()
{

}

bool WSRockObject::Update(float dtime)
{
	m_sprite->m_position = m_body->GetPosition();
	m_sprite->SetAngle(m_body->GetOrientation() /*+270.f*/);

	return true;
}

void WSRockObject::Render()
{
	WSSpriteObject::Render();
	WSPhysicalObject::Render();
}

void WSRockObject::SetSprite(Sprite * sprite)
{
	m_sprite = sprite;
}

void WSRockObject::SetShape(PolygonShape * shape, Vector2f pos)
{
	assert(shape);
	m_shape = shape;

	m_body = m_world->Add(m_shape, pos.x, pos.y);
	m_body->SetOrientation(0.f);
}

Vector2f WSRockObject::GetCameraPosition() const
{
	return m_sprite->m_position;
}

Body* WSRockObject::GetBody() const
{
	return m_body;
}
