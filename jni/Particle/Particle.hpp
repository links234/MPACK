#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include <queue>

#include "Types.hpp"
#include "Maths.hpp"

using namespace Math;

using std::vector;
using std::queue;

class ParticleEffector;
class Texture2D;

class Particle
{
public:
	Particle();
	virtual ~Particle();

	virtual bool Update(GLfloat delta);

	static void UpdateAll(GLfloat delta);
	static void RenderAll();

	Vector2f					m_position;
	Vector2f					m_velocity;
	Vector3f					m_color;
	GLfloat						m_rotation;
	GLfloat						m_angularVelocity;
	GLfloat						m_maxLife;
	GLfloat						m_life;
	Texture2D					*m_texture;
	vector<ParticleEffector*>	*m_modifiers;
private:
	static vector<Particle*>	m_particles;
};

#endif
