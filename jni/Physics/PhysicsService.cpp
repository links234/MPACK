#include "PhysicsService.hpp"

#include "Global.hpp"

namespace Core
{
	PhysicsService::PhysicsService(): m_objectList()
	{
		callback = NULL;
	};

	PObject* PhysicsService::CreateObject(const PShape* p_shape)
	{
		m_objectList.push_back(new Core::PObject(p_shape));
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

	void PhysicsService::Update()
	{
		GLfloat delta=Global::pContext->pTimeService->Elapsed();

		//update state
		for(list<PObject*>::iterator it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			(*it)->Advance(delta);
		}


		//detect collisions
		for(list<PObject*>::iterator it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			list<PObject*>::iterator it2 = it;
			for(it2++; it2 != m_objectList.end(); it2++)
			{
				if(CollideObjects(*(*it), *(*it2)))
				{
					if(callback != NULL)
						callback(*(*it), *(*it2));
				}
			}
		}

	}
}
