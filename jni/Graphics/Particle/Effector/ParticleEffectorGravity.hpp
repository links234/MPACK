#ifndef PARTICLEEFFECTORGRAVITY_HPP
#define PARTICLEEFFECTORGRAVITY_HPP

#include "Types.hpp"
#include "Maths.hpp"
#include "ParticleEffector.hpp"

class ParticleEffectorGravity : public ParticleEffector
{
public:
	ParticleEffectorGravity();
	ParticleEffectorGravity(const Vector2f &gravity);
	virtual ~ParticleEffectorGravity();
	
	void UpdateParticle(Particle* particle, const GLfloat &delta);

	Vector2f m_gravity;
};

#endif 
