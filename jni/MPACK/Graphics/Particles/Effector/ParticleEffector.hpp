#ifndef MPACK_PARTICLEEFFECTOR_HPP
#define MPACK_PARTICLEEFFECTOR_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Particle;
	}
}

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

			static void ClearAll();

		private:
			static std::unordered_set<ParticleEffector*> m_effectors;
		};
	}
}

#endif
