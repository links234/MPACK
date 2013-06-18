#ifndef PARTICLEEFFECTORCOLOR_HPP
#define PARTICLEEFFECTORCOLOR_HPP

#include "Types.hpp"
#include "Maths.hpp"
#include "ParticleEffector.hpp"

class ParticleEffectorColor : public ParticleEffector
{
public:
	ParticleEffectorColor();
	ParticleEffectorColor(const Vector4f &colorStart, const Vector4f &colorEnd);
	virtual ~ParticleEffectorColor();

	void UpdateParticle(Particle* particle, const GLfloat &delta);

	Vector4f m_colorStart,m_colorEnd;
};

#endif
