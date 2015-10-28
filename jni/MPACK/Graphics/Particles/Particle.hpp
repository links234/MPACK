#ifndef MPACK_PARTICLE_HPP
#define MPACK_PARTICLE_HPP

#include <vector>
#include <queue>

#include "Types.hpp"
#include "Math.hpp"
#include "Texture2D.hpp"

namespace MPACK
{
	namespace Graphics
	{
		class ParticleEffector;
		class Sprite;
	}
}

namespace MPACK
{
	namespace Graphics
	{
		class Particle
		{
		public:
			Particle();
			virtual ~Particle();

			virtual bool Update(GLfloat delta);

			static void UpdateAll(GLfloat delta);
			static void RenderAll();
			static void ClearAll();

			static void Cleanup();

			Math::Vector2f					m_position,m_velocity;
			Math::Vector4f					m_color;
			GLfloat							m_rotation,m_angularVelocity;
			GLfloat							m_width,m_height;
			GLfloat							m_life,m_maxLife;
			Texture2D						*m_texture;
			std::vector<ParticleEffector*>	*m_modifiers;
		private:
			static std::vector<Particle*>	m_particles;
			static Sprite				m_spriteInterface;
		};
	}
}

#endif
