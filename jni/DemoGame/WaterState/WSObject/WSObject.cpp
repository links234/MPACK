#include "MPACK.hpp"

#include "WSObject.hpp"

using namespace MPACK;

std::vector <WSObject*> WSObject::s_wsObjects;

WSObject::WSObject()
{
	s_wsObjects.push_back(this);
}

WSObject::~WSObject()
{
	for (std::vector <WSObject*> :: iterator it = s_wsObjects.begin(); it != s_wsObjects.end(); ++ it)
	{
		if (*it == this)
		{
			*it = s_wsObjects.back();
			s_wsObjects.pop_back();
			break;
		}
	}
}

bool WSObject::UpdateAll(float dtime)
{
	std::vector <WSObject*> objects;
	for (std::vector <WSObject*> :: iterator it = s_wsObjects.begin(); it != s_wsObjects.end(); ++ it)
	{
		if ((*it)->Update(dtime))
		{
			objects.push_back(*it);
		}
		else
		{
			delete *it;
		}
	}
	return true;
}

void WSObject::RenderAll()
{
	for ( int i=0;i<s_wsObjects.size();++i)
	{
		s_wsObjects[i]->Render();
	}
}
