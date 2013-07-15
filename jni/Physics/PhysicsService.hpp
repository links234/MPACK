#ifndef PHYSICSSERVICE_HPP
#define PHYSICSSERVICE_HPP

#include "Types.hpp"
#include "PCollide.hpp"
#include "PMath.hpp"

#include <list>

using namespace std;

namespace Core
{
	class PShape;
	class PObject;

	class PhysicsService
	{
	public:
		PhysicsService();

		void AddObject(PObject* pObject);
		void RemoveObject(PObject* pObject);

		void Update(float delta);

		Param2PtrCallbackFunc callback;

	private:
		list<PObject*> m_objectList;
	};
}

#endif
