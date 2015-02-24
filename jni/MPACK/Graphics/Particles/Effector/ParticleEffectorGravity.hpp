#ifndef MPACK_PARTICLEEFFECTORGRAVITY_HPP
#define MPACK_PARTICLEEFFECTORGRAVITY_HPP

#include "Types.hpp"
#include "Math.hpp"
#include "ParticleEffector.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEffectorGravity : public ParticleEffector
		{
		public:
			ParticleEffectorGravity();
			ParticleEffectorGravity(const Vector2f &gravity);
			virtual ~ParticleEffectorGravity();
	
			void UpdateParticle(Particle* particle, const GLfloat &delta);

			Vector2f m_gravity;
		};
	}
}

#endif 
