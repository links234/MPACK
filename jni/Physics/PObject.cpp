#include "PObject.hpp"

namespace Core
{
	PObject::PObject(): m_position(), m_linearVelocity(),
			m_angle(0.0f), m_angularVelocity(), m_shape(NULL),
			m_aabb(), m_userData(NULL), m_iterator() {}

	PObject::PObject(const PShape* p_shape):
			m_position(), m_linearVelocity(), m_angle(0.0f),
			m_angularVelocity(0.0f), m_aabb(), m_userData(NULL)
	{
		if(p_shape->GetType() == PShape::e_poly)
		{
			m_shape = new PPoly(*((PPoly*)p_shape));
		}
		/*else if(p_shape.GetType() == e_circle)
		{
			m_shape = new PCircle(*((PCircle*)p_shape));
		}*/
	}

	void PObject::Advance(float dt)
	{
		//update state
		m_position += m_linearVelocity * dt;
		m_angle += m_angularVelocity * dt;

		//update AABB
		m_shape->ComputeAABB(&m_aabb, m_position, m_angle);


	}
}
