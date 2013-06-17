#include "Particle.hpp"

#include "Random.hpp"
#include "ParticleEffector.hpp"
#include "Debug.hpp"

#include <algorithm>

vector<Particle*>	Particle::m_particles;

struct Particle_cmp
{
	inline bool operator() (const Particle *a, const Particle *b)
	{
		return a->m_texture<b->m_texture;
	}
};

Particle::Particle()
	: m_modifiers(NULL)
{
	m_particles.push_back(this);
}

Particle::~Particle()
{
}

bool Particle::Update(GLfloat delta)
{
	m_life-=delta;
	if(m_life<=0.0f)
	{
		return true;
	}
	if(m_modifiers)
	{
		for(vector<ParticleEffector*>::iterator it=(*m_modifiers).begin();it!=(*m_modifiers).end();++it)
		{
			(*it)->UpdateParticle(this,delta);
		}
	}
	m_position+=m_velocity*delta;
	m_rotation+=m_angularVelocity*delta;
	while(m_rotation>360.0f)
	{
		m_rotation-=360.0f;
	}
	return false;
}

void Particle::UpdateAll(GLfloat delta)
{
	vector<Particle*> temp;
	for(vector<Particle*>::iterator it=m_particles.begin();it!=m_particles.end();++it)
	{
		if(!(*it)->Update(delta))
		{
			temp.push_back(*it);
		}
		else
		{
			delete *it;
		}
	}
	m_particles=temp;
}

void Particle::RenderAll()
{
	//sort(m_particles.begin(),m_particles.end(),Particle_cmp());

	for(vector<Particle*>::iterator it=m_particles.begin();it!=m_particles.end();++it)
	{

	}
}
