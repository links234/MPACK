#include "ParticleEffectorColor.hpp"

#include "Particle.hpp"

using namespace MPACK::Math;

namespace MPACK
{
	namespace Graphics
	{
		ParticleEffectorColor::ParticleEffectorColor()
			: m_colorStart(1.0f,1.0f,1.0f,1.0f), m_colorEnd(1.0f,1.0f,1.0f,0.0f)
		{
		}

		ParticleEffectorColor::ParticleEffectorColor(const Vector4f &colorStart, const Vector4f &colorEnd)
			: m_colorStart(colorStart), m_colorEnd(colorEnd)
		{
		}

		ParticleEffectorColor::~ParticleEffectorColor()
		{
		}

		void ParticleEffectorColor::UpdateParticle(Particle* particle, const GLfloat &delta)
		{
			GLfloat interpolation=particle->m_life/particle->m_maxLife;
			particle->m_color=m_colorStart*interpolation+m_colorEnd*(1.0f-interpolation);
		}
	}
}
