#include "ParticleEmitter.hpp"

#include <vector>

namespace MPACK
{
	namespace Graphics
	{
		std::set<ParticleEmitter*> ParticleEmitter::m_emitters;

		ParticleEmitter::ParticleEmitter()
		{
			m_emitters.insert(this);
		}

		ParticleEmitter::~ParticleEmitter()
		{
			m_emitters.erase(this);
		}

		void ParticleEmitter::Update(GLfloat delta)
		{
		}

		void ParticleEmitter::UpdateAll(GLfloat delta)
		{
			for(std::set<ParticleEmitter*>::iterator it=m_emitters.begin();it!=m_emitters.end();++it)
			{
				(*it)->Update(delta);
			}
		}
	}
}
