#include "ParticleEmitter.hpp"

#include <vector>

std::vector<ParticleEmitter*> ParticleEmitter::m_emitters;

ParticleEmitter::ParticleEmitter()
{
	m_emitters.push_back(this);
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Update(GLfloat delta)
{
}

void ParticleEmitter::UpdateAll(GLfloat delta)
{
	for(std::vector<ParticleEmitter*>::iterator it=m_emitters.begin();it!=m_emitters.end();++it)
	{
		(*it)->Update(delta);
	}
}
