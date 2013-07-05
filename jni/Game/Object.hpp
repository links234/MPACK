#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Maths.hpp"
#include "Sprite.hpp"

#include <vector>

using namespace std;
using namespace Math;

class Object
{
public:
	Object();

	virtual void Update(GLfloat delta);
	virtual void Render();

	virtual ~Object();

	Sprite *m_sprite;
	Vector2f m_velocity;
	Vector2f m_acceleration;
	Vector2f m_direction;
	GLfloat m_frictionDynamic;
	GLfloat m_frictionStatic;
	GLfloat m_maxVelocity;

	static void UpdateAll(GLfloat delta);
	static void RenderAll();

protected:
	static vector<Object*> s_objects;
};

#endif
