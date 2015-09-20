#include "CircleShape.hpp"

#include "Body.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Physics
	{
		CircleShape::CircleShape(float r)
			: radius(r)
		{
		}

		Shape* CircleShape::Clone() const
		{
			return new CircleShape(radius);
		}

		void CircleShape::Initialize()
		{
			ComputeMass(body->m_material.density);
		}

		void CircleShape::ComputeMass(float density)
		{
			body->m_mass=MPACK::Math::Misc<float>::c_Pi*radius*radius*density;
			body->m_inverseMass=(body->m_mass)?1.0f/body->m_mass:0.0f;
			body->m_momentOfInertia=body->m_mass*radius*radius;
			body->m_inverseMomentOfInertia=(body->m_momentOfInertia)?1.0f/body->m_momentOfInertia:0.0f;
		}

		void CircleShape::SetOrientation(float radians)
		{
		}

		Shape::Type CircleShape::GetType() const
		{
			return eCircle;
		}

		void CircleShape::ComputeAABB()
		{
			m_aabb.m_xmax=body->m_position.x+radius;
			m_aabb.m_xmin=body->m_position.x-radius;
			m_aabb.m_ymax=body->m_position.y+radius;
			m_aabb.m_ymin=body->m_position.y-radius;
		}
	}
}
