#ifndef MPACK_PARTICLE_HPP
#define MPACK_PARTICLE_HPP

#include <vector>
#include <queue>

#include "Types.hpp"
#include "Math.hpp"
#include "Texture2D.hpp"

using namespace Math;

using std::vector;
using std::queue;

class ParticleEffector;
class Sprite;

class Particle
{
public:
	Particle();
	virtual ~Particle();

	virtual bool Update(GLfloat delta);

	static void UpdateAll(GLfloat delta);
	static void RenderAll();
	static void Clear();

	Vector2f					m_position,m_velocity;
	Vector4f					m_color;
	GLfloat						m_rotation,m_angularVelocity;
	GLfloat						m_width,m_height;
	GLfloat						m_life,m_maxLife;
	Core::Texture2D				*m_texture;
	vector<ParticleEffector*>	*m_modifiers;
private:
	static vector<Particle*>	m_particles;
	static Sprite				m_spriteInterface;
};

#endif
