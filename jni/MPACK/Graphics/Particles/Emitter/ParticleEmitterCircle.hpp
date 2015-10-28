#ifndef MPACK_PARTICLEEMITTERCIRCLE_HPP
#define MPACK_PARTICLEEMITTERCIRCLE_HPP

#include "ParticleEmitter.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class Texture2D;
	}
}

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEmitterCircle : public ParticleEmitter
		{
		public:
			ParticleEmitterCircle();
			virtual ~ParticleEmitterCircle();

			virtual void Update(GLfloat delta);

			void SetPosition(const Math::Vector2f position);
			void SetVelocity(const GLfloat &min, const GLfloat &max);
			void SetAngularVelocity(const GLfloat &min, const GLfloat &max);
			void SetParticleLife(const GLfloat &min, const GLfloat &max);
			void SetSpawnDelay(const GLfloat &spawnDelay);
			void SetTexture(Texture2D *texture);

		protected:
			Math::Vector2f	m_position;
			GLfloat		m_minVelocity,m_maxVelocity;
			GLfloat		m_minAngularVelocity,m_maxAngularVelocity;
			GLfloat		m_minParticleLife,m_maxParticleLife;
			GLfloat 	m_spawnDelay,m_currentDelay;
			Texture2D 	*m_texture;
		};
	}
}

#endif
