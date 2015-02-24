#include "PObject.hpp"

#include "Global.hpp"
#include "Context.hpp"
#include "PhysicsService.hpp"
#include "Debug.hpp"

const float POBJECT_MAXLINEARVELOCITY=200.0f;

using namespace MPACK::Core;

namespace MPACK
{
	namespace Physics
	{
		PObject::PObject(const PShape* pShape)
			:	m_position(), m_linearVelocity(), m_linearAcceleration(), m_angle(0.0f), m_angularVelocity(0.0f), m_frictionThreshold(0.0f), m_frictionDynamic(0.0f),
				m_maxLinearVelocity(POBJECT_MAXLINEARVELOCITY), m_shape(NULL), m_aabb(), m_userData(NULL)
		{
			if(pShape)
			{
				if(pShape->GetType() == PShape::e_poly)
				{
					m_shape = new PPoly(*((PPoly*)pShape));
				}
				else if(pShape->GetType() == PShape::e_circle)
				{
					m_shape = new PCircle(*((PCircle*)pShape));
				}
			}
			else
			{
				m_shape = new PPoly();
			}

			// Make sure PhysicsService will take care of this PObject
			Global::pContext->pPhysicsService->AddObject(this);
		}

		PObject::~PObject()
		{
			// Clean up what only we can to avoid memoryleaks
			delete m_shape;

			// Make sure PhysicsService does not make SIGSEV trying to update this PObject
			Global::pContext->pPhysicsService->RemoveObject(this);
		}

		void PObject::Advance(float delta)
		{
			// Update linear velocity
			m_linearVelocity+=m_linearAcceleration * delta;
			if(m_linearVelocity.Length()>m_maxLinearVelocity)
			{
				m_linearVelocity.Normalize();
				m_linearVelocity*=m_maxLinearVelocity;
			}

			// Friction system (linear velocity only)
			m_linearVelocity*=(1.0f-m_frictionDynamic * delta);
			if(m_linearVelocity.Length()<m_frictionThreshold)
			{
				m_linearVelocity = PVec2();
			}

			// Update position and rotation
			m_position+=m_linearVelocity * delta;
			m_angle += m_angularVelocity * delta;

			// Update AABB
			m_shape->ComputeAABB(&m_aabb, m_position, m_angle);
		}
	}
}
