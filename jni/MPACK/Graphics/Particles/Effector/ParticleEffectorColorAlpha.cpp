#include "ParticleEffectorColorAlpha.hpp"

#include "Particle.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		ParticleEffectorColorAlpha::ParticleEffectorColorAlpha()
			: m_alphaStart(1.0f), m_alphaEnd(0.0f)
		{
		}

		ParticleEffectorColorAlpha::ParticleEffectorColorAlpha(const double &alphaStart, const double &alphaEnd)
			: m_alphaStart(alphaStart), m_alphaEnd(alphaEnd)
		{
		}

		ParticleEffectorColorAlpha::~ParticleEffectorColorAlpha()
		{
		}

		void ParticleEffectorColorAlpha::UpdateParticle(Particle* particle, const GLfloat &delta)
		{
			GLfloat interpolation=particle->m_life/particle->m_maxLife;
			particle->m_color.w=m_alphaStart*interpolation+m_alphaEnd*(1.0f-interpolation);
		}
	}
}
