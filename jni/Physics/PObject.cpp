#include "PObject.hpp"

const float POBJECT_MAXLINEARVELOCITY=200.0f;

namespace Core
{
	PObject::PObject(const PShape* pShape)
		:	m_position(), m_linearVelocity(), m_linearAcceleration(), m_angle(0.0f), m_angularVelocity(0.0f), m_frictionThreshold(0.0f), m_frictionDynamic(0.0f),
		 	m_maxLinearVelocity(POBJECT_MAXLINEARVELOCITY), m_shape(NULL), m_aabb(), m_userData(NULL)
	{
		if(pShape==NULL)
		{
			return;
		}

		if(pShape->GetType() == PShape::e_poly)
		{
			m_shape = new PPoly(*((PPoly*)pShape));
		}
		/*else if(p_shape.GetType() == e_circle)
		{
			m_shape = new PCircle(*((PCircle*)p_shape));
		}*/
	}

	void PObject::Advance(float delta)
	{
		//update state
		m_linearVelocity+=m_linearAcceleration * delta;
		if(m_linearVelocity.Length()>m_maxLinearVelocity)
		{
			m_linearVelocity.Normalize();
			m_linearVelocity*=m_maxLinearVelocity;
		}

		m_linearVelocity*=(1.0f-m_frictionDynamic * delta);
		if(m_linearVelocity.Length()<m_frictionThreshold)
		{
			m_linearVelocity=Vector2f();
		}

		m_position+=m_linearVelocity * delta;
		m_angle += m_angularVelocity * delta;

		//update AABB
		m_shape->ComputeAABB(&m_aabb, m_position, m_angle);


	}
}
