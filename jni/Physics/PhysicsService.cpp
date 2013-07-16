#include "PhysicsService.hpp"

#include "Global.hpp"

namespace Core
{
	PhysicsService::PhysicsService(): m_objectList()
	{
		callback = NULL;
	};

	void PhysicsService::AddObject(PObject* pObject)
	{
		m_objectList.push_back(pObject);
		list<PObject*>::iterator it = m_objectList.end();
		--it;
		(*it)->m_iterator = it;
	}

	void PhysicsService::RemoveObject(PObject* pObject)
	{
		m_objectList.erase(pObject->m_iterator);
	}

	void PhysicsService::Update(float delta)
	{
		//update state
		for(list<PObject*>::iterator it = m_objectList.begin(); it != m_objectList.end(); it++)
		{
			(*it)->Advance(delta);
		}


		//detect collisions
		for(list<PObject*>::iterator first = m_objectList.begin(); first != m_objectList.end(); first++)
		{
			list<PObject*>::iterator second = first;
			for(second++; second != m_objectList.end(); second++)
			{
				if(PCollide::CollideObjects(*(*first), *(*second)))
					if(callback != NULL)
					{
						callback((void*)(*first), (void*)(*second));
					}
				}
			}
		}

	}
}
