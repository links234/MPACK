#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include <set>

#include "Particle.hpp"

class ParticleEmitter
{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	virtual void Update(GLfloat delta);

	static void UpdateAll(GLfloat delta);

private:
	static std::set<ParticleEmitter*> m_emitters;
};

#endif
