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
	vector<Object*> whatDelete;
	for(vector<Object*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
	{
		if(!(*it)->Update(delta))
		{
			whatDelete.push_back(*it);
		}
	}
	for(vector<Object*>::iterator it=whatDelete.begin();it!=whatDelete.end();++it)
	{
		delete *it;
	}
}

void Object::RenderAll()
{
	for(vector<Object*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
	{
		(*it)->Render();
	}
}

void Object::ClearAll()
{
	vector<Object*> whatDelete;
	for(vector<Object*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
	{
		whatDelete.push_back(*it);
	}
	for(vector<Object*>::iterator it=whatDelete.begin();it!=whatDelete.end();++it)
	{
		delete *it;
	}
}
