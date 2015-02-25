#ifndef MPACK_PARTICLEEFFECTORCOLOR_HPP
#define MPACK_PARTICLEEFFECTORCOLOR_HPP

#include "Types.hpp"
#include "Math.hpp"
#include "ParticleEffector.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEffectorColor : public ParticleEffector
		{
		public:
			ParticleEffectorColor();
			ParticleEffectorColor(const Math::Vector4f &colorStart, const Math::Vector4f &colorEnd);
			virtual ~ParticleEffectorColor();

			void UpdateParticle(Particle* particle, const GLfloat &delta);

			Math::Vector4f m_colorStart,m_colorEnd;
		};
	}
}

#endif
