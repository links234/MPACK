#ifndef MPACK_PARTICLEEMITTER_HPP
#define MPACK_PARTICLEEMITTER_HPP

#include <set>

#include "Particle.hpp"

class ParticleEmitter
{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	virtual void Update(GLfloat delta);

	static void UpdateAll(GLfloat delta);

	vector<ParticleEffector*>	m_modifiers;
private:
	static std::set<ParticleEmitter*> m_emitters;
};

#endif
