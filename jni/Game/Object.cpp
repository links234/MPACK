#include "Object.hpp"

#include "Global.hpp"

#include <algorithm>

vector<Object*> Object::s_objects;

Object::Object()
	: m_sprite(NULL), m_velocity(), m_acceleration(), m_direction(), m_maxVelocity(200.0f), m_frictionDynamic(0.55f),  m_frictionStatic(2.5f)
{
	s_objects.push_back(this);
}

void Object::Update(GLfloat delta)
{
	m_velocity+=m_acceleration*delta;
	if(m_velocity.Length()>m_maxVelocity)
	{
		m_velocity.Normalize();
		m_velocity*=m_maxVelocity;
	}

	m_velocity*=(1.0f-m_frictionDynamic*delta);
	if(m_velocity.Length()<m_frictionStatic)
	{
		m_velocity=Vector2f();
	}

	m_sprite->m_position+=m_velocity*delta;
	if(m_direction.Length())
	{
		m_sprite->m_rotation=m_direction.Angle();
		Debug::Print(Global::pFont,"Angle = %f",m_direction.Angle());
	}
}

void Object::Render()
{
	m_sprite->Render();
}

Object::~Object()
{
	for(vector<Object*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
	{
		if(this==*it)
		{
			*it=s_objects[s_objects.size()-1];
			s_objects.pop_back();
			break;
		}
	}
}

void Object::UpdateAll(GLfloat delta)
{
	for(vector<Object*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
	{
		(*it)->Update(delta);
	}
}

void Object::RenderAll()
{
	for(vector<Object*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
	{
		(*it)->Render();
	}
}
