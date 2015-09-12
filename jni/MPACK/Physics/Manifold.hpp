#ifndef MPACK_MANIFOLD_HPP
#define MPACK_MANIFOLD_HPP

#include "Math.hpp"

namespace MPACK
{
	namespace Physics
	{
		class World;
		class Body;
		class Collider;
	}
}

namespace MPACK
{
	namespace Physics
	{
		class Manifold
		{
		public:
			Manifold(Body *A, Body *B);

			void Solve();
			void Initialize();
			void ApplyImpulse();
			void PositionalCorrection();
			void InfiniteMassCorrection();

		private:
			Body *m_A;
			Body *m_B;

			float m_restitution;
			float m_dynamicFriction;
			float m_staticFriction;

			float m_penetration;
			MPACK::Math::Vector2f m_normal;
			MPACK::Math::Vector2f m_contacts[2];
			int m_contactCount;

			friend class World;
			friend class Collider;
		};
	}
}

#endif
