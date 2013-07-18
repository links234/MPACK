#include "Object.hpp"

#include "Global.hpp"

#include <algorithm>

vector<Object*> Object::s_objects;

Object::Object()
	: m_debugInCollision(true)
{
	s_objects.push_back(this);
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
