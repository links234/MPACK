#ifndef MPACK_BODY_HPP
#define MPACK_BODY_HPP

#include "Math.hpp"

namespace MPACK
{
	namespace Physics
	{
		class World;
		class Manifold;
		class Collider;
		class Shape;
		class CircleShape;
		class PolygonShape;
	}
}

namespace MPACK
{
	namespace Physics
	{
		class Body
		{
		public:
			Body(Shape *shape);
			~Body();

			void ApplyForce(const MPACK::Math::Vector2f& force);
			void ApplyImpulse(const MPACK::Math::Vector2f& impulse, const MPACK::Math::Vector2f& contactVector);
			void ApplyTorque(const float torque);

			void SetStatic();

			void LockOrientation();
			void UnlockOrientation();

			void SetOrientation(float orientation);
			void SetPosition(MPACK::Math::Vector2f position);

			float GetOrientation() const;
			MPACK::Math::Vector2f GetPosition() const;

			float GetMass() const;

		private:
			void IntegrateForces(float delta);
			void IntegrateVelocity(float delta);

			void ResetForces();

			MPACK::Math::Vector2f m_position;
			MPACK::Math::Vector2f m_velocity;

			float m_angularVelocity;
			float m_torque;
			float m_orientation;

			MPACK::Math::Vector2f m_force;

			float m_momentOfInertia;
			float m_inverseMomentOfInertia;
			float m_mass;
			float m_inverseMass;

			float m_tempMomentOfInertia;
			float m_tempInverseMomentOfInertia;
			float m_tempMass;
			float m_tempInverseMass;

			float m_staticFriction;
			float m_dynamicFriction;
			float m_restitution;

			Shape *m_shape;

			friend class MPACK::Physics::World;
			friend class Collider;
			friend class Manifold;
			friend class Shape;
			friend class CircleShape;
			friend class PolygonShape;
		};
	}
}

#endif
