#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include "Object.hpp"
#include "Maths.hpp"

#include <vector>

using namespace std;
using namespace Math;

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void Update(GLfloat delta);

	void Transform(Vector2f &vertex) const;
	void SetPosition(const Vector2f &position);
	void Link(Object *target=NULL);

	void EnableSpringSystem();
	void DisableSpringSystem();

	void SetSpringConstant(const GLfloat &springConstant);

	void 	SetScale(const GLfloat &scale);
	GLfloat GetScale() const;

	void 		RotateDirection(const GLfloat &angle);
	void 		SetDirection(const Vector2f &direction);
	Vector2f 	GetDirection() const;

	static void UpdateAll(GLfloat delta);

private:
	Vector2f	m_position,m_velocity;
	Vector2f 	m_idealPosition;
	Object		*m_target;

	GLfloat		m_springConstant,m_dampingConstant;
	bool		m_useSpringSystem;

	GLfloat 	m_scale;

	Vector2f	m_direction;

	static vector<Camera2D*> s_cameras;
};

#endif
