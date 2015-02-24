#ifndef MPACK_PARTICLEEFFECTOR_HPP
#define MPACK_PARTICLEEFFECTOR_HPP

#include "Particle.hpp"
#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEffector
		{
		public:
			ParticleEffector();
			virtual ~ParticleEffector();

			virtual void UpdateParticle(Particle* particle, const GLfloat &delta) = 0;
		};
	}
}

#endif
