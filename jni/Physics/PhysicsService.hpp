#ifndef PHYSICSSERVICE_HPP
#define PHYSICSSERVICE_HPP

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

		PObject* CreateObject(const PShape* shape);
		void DestroyObject(PObject* p_object);

		void Update();

		void (*callback)(PObject& obj1, PObject& obj2); //final version will have a third parameter

	private:
		list<PObject*> m_objectList;
	};
}

#endif
