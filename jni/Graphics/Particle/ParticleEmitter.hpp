#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include <vector>

#include "Types.hpp"

class ParticleEmitter
{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	virtual void Update(GLfloat delta);

	static void UpdateAll(GLfloat delta);

private:
	static std::vector<ParticleEmitter*> m_emitters;
};

#endif
