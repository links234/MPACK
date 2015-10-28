#include "ParticleEffector.hpp"

#include "Particle.hpp"

using namespace std;

namespace MPACK
{
	namespace Graphics
	{
		unordered_set<ParticleEffector*> ParticleEffector::m_effectors;

		ParticleEffector::ParticleEffector()
		{
			m_effectors.insert(this);
		}

		ParticleEffector::~ParticleEffector()
		{
			m_effectors.erase(this);
		}

		void ParticleEffector::ClearAll()
		{
			vector<ParticleEffector*> whatDel;
			for(unordered_set<ParticleEffector*>::iterator it=m_effectors.begin();it!=m_effectors.end();++it)
			{
				whatDel.push_back(*it);
			}
			for(vector<ParticleEffector*>::iterator it=whatDel.begin();it!=whatDel.end();++it)
			{
				delete *it;
			}
		}
	}
}
