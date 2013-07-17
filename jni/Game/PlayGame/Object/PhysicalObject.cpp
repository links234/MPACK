#include "PhysicalObject.hpp"

PhysicalObject::PhysicalObject()
{
}

PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::Update(GLfloat delta)
{
}

void PhysicalObject::Render()
{
}

Vector2f PhysicalObject::GetCameraPosition() const
{
	return m_position;
}
