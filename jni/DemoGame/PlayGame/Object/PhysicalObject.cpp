#include "PhysicalObject.hpp"

#include "Batcher.hpp"

using namespace MPACK;
using namespace MPACK::Physics;

PhysicalObject::PhysicalObject(MPACK::Physics::World *world)
	: m_body(NULL), m_world(world), m_shape(NULL)
{
}

PhysicalObject::~PhysicalObject()
{
}

bool PhysicalObject::Update(GLfloat delta)
{
	return true;
}

void PhysicalObject::Render()
{
	if(m_shape)
	{
		Vector4f GREEN=Vector4f(0.0f,1.0f,0.0f,1.0f);
		Vector4f RED=Vector4f(1.0f,0.0f,0.0f,1.0f);
		Vector4f color=GREEN;
		if(m_debugInCollision)
		{
			color=RED;
		}

		TransformState2f transformState=TransformState2f(m_body->GetPosition(),MPACK::Math::Misc<float>::RadToDeg(m_body->GetOrientation()),1.0f);
		if(m_shape->GetType()==Shape::ePoly)
		{
			PolygonShape *poly=(PolygonShape*)(m_shape);
			Batcher::SendDebugPolygon((Vector2f*)poly->m_vertices,poly->m_vertexCount,color,transformState);
		}
		/*//
		else if(m_shape->m_type==PShape::e_circle)
		{
			PCircle *circle=(PCircle*)(m_shape);
			transformState.SetScale(circle->GetRadius());
			Batcher::SendDebugCircle(Debug::circlePoints,color,transformState);
		}*/
	}
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
