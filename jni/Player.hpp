#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Maths.hpp"
#include "Types.hpp"

using namespace Math;

class Player
{
public:
	Player();

	void Update(GLfloat delta);
	void Render();

	void SetFriction(GLfloat friction);
	void SetMinFriction(GLfloat minFriction);

	~Player();
private:
	GLfloat 	m_friction;
	GLfloat		m_minFriction;
	Vector2f	m_position;
	Vector2f 	m_velocity;
	Vector2f	m_acceleration;
};

#endif
