#include "Manifold.hpp"

#include "Body.hpp"
#include "Shape.hpp"
#include "Collider.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Physics
	{
		Manifold::Manifold(Body *A, Body *B)
			: m_A(A), m_B(B), m_restitution(1.0f), m_staticFriction(0.0f), m_dynamicFriction(0.0f),
			  m_contactCount(0), m_penetration(0.0f)
		{
		}

		void Manifold::Solve()
		{
			Collider::Dispatch[m_A->m_shape->GetType()][m_B->m_shape->GetType()](this,m_A,m_B);
		}

		void Manifold::Initialize()
		{
			m_restitution=Misc<float>::Min(m_A->m_material.restitution,m_B->m_material.restitution);

			m_staticFriction=Misc<float>::Sqrt(m_A->m_material.staticFriction*m_B->m_material.staticFriction);
			m_dynamicFriction=Misc<float>::Sqrt(m_A->m_material.dynamicFriction*m_B->m_material.dynamicFriction);

			for(int i=0;i<m_contactCount;++i)
			{
				Vector2f ra=m_contacts[i]-m_A->m_position;
				Vector2f rb=m_contacts[i]-m_B->m_position;

				Vector2f rv=m_B->m_velocity+Cross(m_B->m_angularVelocity,rb)-
						  m_A->m_velocity-Cross(m_A->m_angularVelocity,ra);
			}
		}

		void Manifold::ApplyImpulse()
		{
			if(Misc<float>::Equal(m_A->m_inverseMass+m_B->m_inverseMass,0))
			{
				InfiniteMassCorrection();
				return;
			}

			for(int i=0;i<m_contactCount;++i)
			{
				Vector2f ra=m_contacts[i]-m_A->m_position;
				Vector2f rb=m_contacts[i]-m_B->m_position;

				Vector2f rv = m_B->m_velocity+Cross(m_B->m_angularVelocity,rb)-
						m_A->m_velocity-Cross(m_A->m_angularVelocity,ra);

				float contactVel=Dot(rv,m_normal);

				if(contactVel>0)
				{
					return;
				}

				float raCrossN=Cross(ra,m_normal);
				float rbCrossN=Cross(rb,m_normal);
				float invMassSum=m_A->m_inverseMass+m_B->m_inverseMass+Misc<float>::Sqr(raCrossN)*m_A->m_inverseMomentOfInertia+Misc<float>::Sqr(rbCrossN)*m_B->m_inverseMomentOfInertia;

				float j=-(1.0f+m_restitution)*contactVel;
				j/=invMassSum;
				j/=(float)m_contactCount;

				Vector2f impulse=m_normal*j;
				m_A->ApplyImpulse(-impulse,ra);
				m_B->ApplyImpulse(impulse,rb);

				rv=m_B->m_velocity+Cross(m_B->m_angularVelocity,rb)-
						m_A->m_velocity-Cross( m_A->m_angularVelocity, ra);

				Vector2f t=rv-(m_normal*Dot(rv,m_normal));
				t.Normalize();

				float jt=-Dot(rv,t);
				jt/=invMassSum;
				jt/=(float)m_contactCount;

				if(Misc<float>::Equal(jt,0.0f))
				{
					return;
				}

				Vector2f tangentImpulse;
				if(std::abs(jt)<j*m_staticFriction)
				{
					tangentImpulse=t*jt;
				}
				else
				{
					tangentImpulse=t*-j*m_dynamicFriction;
				}

				m_A->ApplyImpulse(-tangentImpulse,ra);
				m_B->ApplyImpulse(tangentImpulse,rb);
			}
		}

		void Manifold::PositionalCorrection( void )
		{
			const float k_slop=0.05f;
			const float percent=0.4f;
			Vector2f correction=(Misc<float>::Max(m_penetration-k_slop,0.0f)/(m_A->m_inverseMass+m_B->m_inverseMass))*m_normal*percent;
			m_A->m_position-=correction*m_A->m_inverseMass;
			m_B->m_position+=correction*m_B->m_inverseMass;
		}

		void Manifold::InfiniteMassCorrection( void )
		{
			m_A->m_velocity.Set(0,0);
			m_B->m_velocity.Set(0,0);
		}
	}
}
