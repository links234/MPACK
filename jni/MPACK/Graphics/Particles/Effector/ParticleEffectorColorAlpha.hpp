#ifndef MPACK_PARTICLEEFFECTORCOLORALPHA_HPP
#define MPACK_PARTICLEEFFECTORCOLORALPHA_HPP

#include "Types.hpp"
#include "Math.hpp"
#include "ParticleEffector.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEffectorColorAlpha : public ParticleEffector
		{
		public:
			ParticleEffectorColorAlpha();
			ParticleEffectorColorAlpha(const double &alphaStart, const double &alphaEnd);
			virtual ~ParticleEffectorColorAlpha();

			void UpdateParticle(Particle* particle, const GLfloat &delta);

			double m_alphaStart,m_alphaEnd;
		};
	}
}

#endif
