#ifndef PARTICLEEFFECTORGRAVITY_HPP
#define PARTICLEEFFECTORGRAVITY_HPP

#include "Types.hpp"
#include "Maths.hpp"
#include "ParticleEffector.hpp"

class ParticleGravity : public ParticleEffector
{
public:
	ParticleGravity();
	ParticleGravity(const Vector2f &gravity);
	virtual ~ParticleGravity();
	
	void UpdateParticle(Particle* particle, const GLfloat &delta);

	Vector2f m_gravity;
};

#endif 
