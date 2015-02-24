#include "ParticleEffectorGravity.hpp"

#include "Particle.hpp"

namespace MPACK
{
	namespace Graphics
	{
		ParticleEffectorGravity::ParticleEffectorGravity()
			: m_gravity(0.0f,9.8f)
		{
		}

		ParticleEffectorGravity::ParticleEffectorGravity(const Vector2f &gravity)
			: m_gravity(gravity)
		{
		}

		ParticleEffectorGravity::~ParticleEffectorGravity()
		{
		}

		void ParticleEffectorGravity::UpdateParticle(Particle* particle, const GLfloat &delta)
		{
			particle->m_velocity+=m_gravity*delta;
		}
	}
}
