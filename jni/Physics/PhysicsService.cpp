#include "PhysicsService.hpp"

namespace Core
{
	PhysicsService::PhysicsService(): m_objectList() {};

	PObject* PhysicsService::CreateObject(Pshape p_shape)
	{
		m_objectList.push_back(new PShape(p_shape));
		list<PObject*>::iterator it = m_objectList.end();
		it--;
		(*it)->m_iterator = it;

		return *it;
	}

	void PhysicsService::DestroyObject(PObject* p_object)
	{
		list<PObject*>::iterator it =  p_object->m_iterator;
		delete (*it);
		m_objectList.erase(it);
	}

	void PhysicsService::Step(float delta_time)
	{
		//update state
		for(list<PObject*>::iterator it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			(*it)->advance(delta_time);
		}


		//detect collisions
		for(list<PObject*>::iterator it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			for(list<PObject*>::iterator it2 = it+1; it2 != m_objectList.end(); it2++)
			{
				if(CollideObjects(*(*it), *(*it2)))
				{
					callback(*(*it), *(*it2));
				}
			}
		}
	}
}
