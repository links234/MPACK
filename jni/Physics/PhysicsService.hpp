#ifndef PHYSICSSERVICE_HPP
#define PHYSICSSERVICE_HPP

#include "Types.hpp"
#include "Vector2.hpp"
#include "AABB1D.hpp"
#include "AABB2D.hpp"

#include "PShape.hpp"
#include "PObject.hpp"
#include "PCollide.hpp"

#include <list>

typedef Vector2<float> PVec2;
typedef AABB2D<float> PAABB;
typedef AABB1D<float> PSegm;

using namespace std;

namespace Core
{
	class PhysicsService
	{
	public:
		PhysicsService();

		PObject* CreateObject(PShape shape);
		void DestroyObject(PObject* p_object);

		void Step(float delta_time);

		void (*callback)(PObject& obj1, PObject& obj2); //final version will have a third parameter

	private:
		list<PObject*> m_objectList;
	};
}

#endif
