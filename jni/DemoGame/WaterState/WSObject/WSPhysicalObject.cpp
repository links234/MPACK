#include "WSPhysicalObject.hpp"
#include <cassert>

using namespace MPACK;
using namespace MPACK::Physics;
using namespace MPACK::Math;

WSPhysicalObject::WSPhysicalObject(World * world)
: m_world(world)
, m_shape(NULL)
, m_body(NULL)
{
	assert(world);
}

WSPhysicalObject::~WSPhysicalObject()
{
	m_world->Destroy(m_body);
	m_world = NULL;
}

bool WSPhysicalObject::Update(float dtime)
{
	// !?
	return true;
}

void WSPhysicalObject::Render()
{

}

void WSPhysicalObject::SetPosition(Vector2f pos)
{
	assert(m_body);
	m_body->SetPosition(pos);
}

void WSPhysicalObject::SetLinearAcceleration(Vector2f force)
{
	assert(m_body);
	m_body->ApplyForce(force * m_body->GetMass());
}

void WSPhysicalObject::SetShape(PolygonShape * shape, Vector2f pos)
{
	assert(shape);
	m_shape = shape;
	m_body = m_world->Add(shape, pos.x, pos.y);

	m_body->SetOrientation(0.f);
}

Vector2f WSPhysicalObject::GetCameraPosition() const
{
	return m_body->GetPosition();
}

Body* WSPhysicalObject::GetBody() const
{
	return m_body;
}

PolygonShape* WSPhysicalObject::GetShape() const
{
	return (PolygonShape*)m_body->GetShape();
}
