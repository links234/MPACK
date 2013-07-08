#include "PCollide.hpp"

namespace Core
{
	bool CollideObjects(const PObject& obj1, const PObject& obj2)
	{
		if(!obj1.GetAABB().Intersect(obj2.GetAABB()))
		{
			return false;
		}

		return true;

		if(obj1.GetShape()->GetType() == PShape::e_poly && obj2.GetShape()->GetType() == PShape::e_poly)
		{
			PPoly &s1 = *((PPoly*)obj1.GetShape()),
				  &s2 = *((PPoly*)obj2.GetShape());


		}

	}
}
