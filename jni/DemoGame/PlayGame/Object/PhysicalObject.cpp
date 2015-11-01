#include "PhysicalObject.hpp"

#include "Batcher.hpp"

using namespace MPACK;
using namespace MPACK::Physics;

PhysicalObject::PhysicalObject(MPACK::Physics::World *world)
	: m_body(NULL), m_world(world), m_shape(NULL), inCollision(false)
{
}

PhysicalObject::~PhysicalObject()
{
	if(m_shape)
	{
		delete m_shape;
		m_shape = NULL;
	}
	if(m_body)
	{
		m_world->Destroy(m_body);
		m_body = NULL;
	}
}

bool PhysicalObject::Update(GLfloat delta)
{
	return true;
}

void PhysicalObject::Render()
{
	m_debugInCollision=false;
}

Vector2f PhysicalObject::GetCameraPosition() const
{
	return m_body->GetPosition();
}

void PhysicalObject::SetPosition(Vector2f pos)
{
	m_body->SetPosition(pos);
}

void PhysicalObject::SetLinearAcceleration(Vector2f force)
{
	m_body->ApplyForce(force*m_body->GetMass());
}
