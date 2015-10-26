#include "ParticleEmitter.hpp"

#include "Particle.hpp"

using namespace std;

namespace MPACK
{
	namespace Graphics
	{
		unordered_set<ParticleEmitter*> ParticleEmitter::m_emitters;

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
			for(unordered_set<ParticleEmitter*>::iterator it=m_emitters.begin();it!=m_emitters.end();++it)
			{
				(*it)->Update(delta);
			}
		}

		void ParticleEmitter::ClearAll()
		{
			vector<ParticleEmitter*> whatDel;
			for(unordered_set<ParticleEmitter*>::iterator it=m_emitters.begin();it!=m_emitters.end();++it)
			{
				whatDel.push_back(*it);
			}
			for(vector<ParticleEmitter*>::iterator it=whatDel.begin();it!=whatDel.end();++it)
			{
				delete *it;
			}
		}
	}
}
