#include "ParticleEffectorGravity.hpp"

#include "Particle.hpp"

ParticleGravity::ParticleGravity()
	: m_gravity(0.0f,-5.0f)
{
}

ParticleGravity::ParticleGravity(const Vector2f &gravity)
	: m_gravity(gravity)
{
}

ParticleGravity::~ParticleGravity()
{
}

void ParticleGravity::UpdateParticle(Particle* particle, const GLfloat &delta)
{
	particle->m_velocity+=m_gravity*delta;
}
