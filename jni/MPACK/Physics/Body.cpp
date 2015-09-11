#include "Body.hpp"

#include "Shape.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Physics
	{
		Body::Body(Shape *shape)
		  : m_shape(shape->Clone())
		{
			m_shape->body = this;
			m_position.Set(0,0);
			m_velocity.Set(0,0);
			m_angularVelocity=0;
			m_torque=0;
			m_orientation=0.0f;
			m_force.Set(0,0);
			m_staticFriction=0.5f;
			m_dynamicFriction=0.3f;
			m_restitution=0.2f;

			m_momentOfInertia=0.0f;
			m_inverseMomentOfInertia=0.0f;
			m_mass=0.0f;
			m_inverseMass=0.0f;

			m_shape->Initialize();

			m_tempMomentOfInertia=m_momentOfInertia;
			m_tempInverseMomentOfInertia=m_inverseMomentOfInertia;
			m_tempMass=m_mass;
			m_tempInverseMass=m_inverseMass;
		}

		Body::~Body()
		{
			delete m_shape;
		}

		void Body::ApplyForce(const Vector2f& force)
		{
			m_force+=force;
		}

		void Body::ApplyImpulse(const Vector2f& m_inverseMasspulse, const Vector2f& contactVector)
		{
			m_velocity += m_inverseMass*m_inverseMasspulse;
			m_angularVelocity += m_inverseMomentOfInertia*Cross(contactVector,m_inverseMasspulse);
		}

		void Body::SetStatic()
		{
			m_momentOfInertia=0.0f;
			m_inverseMomentOfInertia=0.0f;
			m_mass=0.0f;
			m_inverseMass=0.0f;
			m_velocity=Vector2f();
		}

		void Body::LockOrientation()
		{
			m_momentOfInertia=0.0f;
			m_inverseMomentOfInertia=0.0f;
			m_angularVelocity=0.0f;
		}

		void Body::UnlockOrientation()
		{
			m_momentOfInertia=m_tempMomentOfInertia;
			m_inverseMomentOfInertia=m_tempInverseMomentOfInertia;
		}

		void Body::SetOrientation(float orientation)
		{
			orientation=MPACK::Math::Misc<float>::DegToRad(orientation);
			m_orientation=orientation;
			m_shape->SetOrientation(orientation);
		}

		void Body::SetPosition(Vector2f position)
		{
			m_position=position;
		}

		float Body::GetOrientation() const
		{
			return MPACK::Math::Misc<float>::RadToDeg(m_orientation);
		}

		MPACK::Math::Vector2f Body::GetPosition() const
		{
			return m_position;
		}

		float Body::GetMass() const
		{
			return m_mass;
		}

		void Body::IntegrateForces(float delta)
		{
			if(m_inverseMass == 0.0f)
			{
				return;
			}

			delta*=0.5f;

			m_velocity+=(m_force*m_inverseMass)*delta;
			m_angularVelocity+=m_torque*m_inverseMomentOfInertia*delta;
		}

		void Body::IntegrateVelocity(float delta)
		{
			if(m_inverseMass == 0.0f)
			{
				return;
			}

			m_position += m_velocity*delta;
			m_orientation += m_angularVelocity*delta;
			m_shape->SetOrientation(m_orientation);
			IntegrateForces(delta);
		}

		void Body::ResetForces()
		{
			m_force.Set(0.0f,0.0f);
			m_torque=0.0f;
		}
	}
}
