#include "PhysicalObject.hpp"

#include "SpriteBatcher.hpp"

PhysicalObject::PhysicalObject()
{
	m_objectType=Object::t_PhysicalObject;
	m_userData=this;
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
		TransformState2f transformState=TransformState2f(m_position,m_angle,1.0f);
		if(m_shape->m_type==PShape::e_poly)
		{
			PPoly *poly=(PPoly*)(m_shape);
			SpriteBatcher::SendDebugPolygon(&poly->GetVertex(0),poly->GetVertexCount(),color,transformState);
		}

		else if(m_shape->m_type==PShape::e_circle)
		{
			PCircle *circle=(PCircle*)(m_shape);
			transformState.SetScale(circle->GetRadius());
			SpriteBatcher::SendDebugCircle(Debug::circlePoints,color,transformState);
		}
	}
	m_debugInCollision=false;
}

Vector2f PhysicalObject::GetCameraPosition() const
{
	return m_position;
}
