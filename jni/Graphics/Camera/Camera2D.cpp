#include "Camera2D.hpp"

#include "Render.hpp"

const	GLfloat	DEFAULT_CAMERA2D_DIRECTION_X	=	1.0f;
const	GLfloat DEFAULT_CAMERA2D_DIRECTION_Y	=	0.0f;
const 	GLfloat	DEFAULT_CAMERA2D_SCALE			=	1.0f;
const 	GLfloat	DEFAULT_CAMERA2D_SPRINGCONSTANT	=	50.0f;
const 	bool	DEFAULT_CAMERA2D_SPRINGSYSTEM	=	true;

vector<Camera2D*> Camera2D::s_cameras;

Camera2D::Camera2D()
	: m_position(), m_velocity(), m_target(NULL), m_idealPosition(), m_useSpringSystem(DEFAULT_CAMERA2D_SPRINGSYSTEM), m_scale(DEFAULT_CAMERA2D_SCALE),
	  m_direction(DEFAULT_CAMERA2D_DIRECTION_X,DEFAULT_CAMERA2D_DIRECTION_Y)
{
	s_cameras.push_back(this);
	SetSpringConstant(DEFAULT_CAMERA2D_SPRINGCONSTANT);
}

Camera2D::~Camera2D()
{
	for(vector<Camera2D*>::iterator it=s_cameras.begin();it!=s_cameras.end();++it)
	{
		if(this==*it)
		{
			*it=s_cameras[s_cameras.size()-1];
			s_cameras.pop_back();
			break;
		}
	}
}

void Camera2D::Update(GLfloat delta)
{
	if(m_target)
	{
		SetPosition(m_target->m_sprite->m_position);
	}

	if(m_useSpringSystem)
	{
		Vector2f displacement = m_position - m_idealPosition;
		Vector2f springAcceleration = (displacement * (-m_springConstant)) - (m_velocity * m_dampingConstant);

		m_velocity += springAcceleration * delta;
		m_position += m_velocity * delta;
	}
	else
	{
		m_position=m_idealPosition;
	}
}

void Camera2D::Transform(Vector2f &vertex) const
{
	vertex-=m_position;
	vertex*=m_scale;

	vertex.Rotate(-m_direction.Angle());

	vertex+=Vector2f(Render::GetScreenWidth()*0.5f,Render::GetScreenHeight()*0.5f);
}

void Camera2D::SetPosition(const Vector2f &position)
{
	m_idealPosition=position;
}

void Camera2D::Link(Object *target)
{
	m_target=target;
}

void Camera2D::EnableSpringSystem()
{
	m_useSpringSystem=true;
}

void Camera2D::DisableSpringSystem()
{
	m_useSpringSystem=false;
}

void Camera2D::SetSpringConstant(const GLfloat &springConstant)
{
	m_springConstant = springConstant;
	m_dampingConstant = 2.0f * Misc<GLfloat>::Sqrt(springConstant);
}

void Camera2D::SetScale(const GLfloat &scale)
{
	m_scale=scale;
}

GLfloat Camera2D::GetScale() const
{
	return m_scale;
}

void Camera2D::RotateDirection(const GLfloat &angle)
{
	m_direction.Rotate(angle);
}

void Camera2D::SetDirection(const Vector2f &direction)
{
	m_direction=direction;
}

Vector2f Camera2D::GetDirection() const
{
	return m_direction;
}

void Camera2D::UpdateAll(GLfloat delta)
{
	for(vector<Camera2D*>::iterator it=s_cameras.begin();it!=s_cameras.end();++it)
	{
		(*it)->Update(delta);
	}
}
