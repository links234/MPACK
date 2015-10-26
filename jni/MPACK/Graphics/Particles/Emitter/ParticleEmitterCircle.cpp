#include "ParticleEmitterCircle.hpp"

#include "Particle.hpp"
#include "Texture2D.hpp"
#include "Random.hpp"

using namespace MPACK::Math;
using namespace MPACK::Graphics;

namespace MPACK
{
	namespace Graphics
	{
		ParticleEmitterCircle::ParticleEmitterCircle()
			: m_spawnDelay(0.0f), m_currentDelay(0.0f),
			  m_minVelocity(0.0f), m_maxVelocity(0.0f),
			  m_minAngularVelocity(0.0f), m_maxAngularVelocity(0.0f),
			  m_minParticleLife(0.0f), m_maxParticleLife(0.0f),
			  m_texture(NULL)
		{
		}

		ParticleEmitterCircle::~ParticleEmitterCircle()
		{

		}

		void ParticleEmitterCircle::Update(GLfloat delta)
		{
			m_currentDelay+=delta;
			while(m_currentDelay>=m_spawnDelay)
			{
				m_currentDelay-=m_spawnDelay;
				Particle *pParticle=new Particle;
				pParticle->m_position=m_position;
				pParticle->m_angularVelocity=Core::Random::Double(m_minAngularVelocity,m_maxAngularVelocity);
				pParticle->m_maxLife=Core::Random::Double(m_minParticleLife,m_maxParticleLife);
				pParticle->m_life=pParticle->m_maxLife;
				pParticle->m_texture=m_texture;
				Vector2f velocity(1.0f,0.0f);
				velocity.Rotate(Core::Random::Double(0.0f,360.0f));
				pParticle->m_velocity=velocity*Core::Random::Double(m_minVelocity,m_maxVelocity);
				pParticle->m_modifiers=&m_modifiers;
			}
		}

		void ParticleEmitterCircle::SetPosition(const Vector2f position)
		{
			m_position=position;
		}

		void ParticleEmitterCircle::SetVelocity(const GLfloat &min, const GLfloat &max)
		{
			m_minVelocity=min;
			m_maxVelocity=max;
		}

		void ParticleEmitterCircle::SetAngularVelocity(const GLfloat &min, const GLfloat &max)
		{
			m_minAngularVelocity=min;
			m_maxAngularVelocity=max;
		}

		void ParticleEmitterCircle::SetParticleLife(const GLfloat &min, const GLfloat &max)
		{
			m_minParticleLife=min;
			m_maxParticleLife=max;
		}

		void ParticleEmitterCircle::SetSpawnDelay(const GLfloat &spawnDelay)
		{
			m_spawnDelay=spawnDelay;
		}

		void ParticleEmitterCircle::SetTexture(Texture2D *texture)
		{
			m_texture=texture;
		}
	}
}

