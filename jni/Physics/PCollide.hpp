#ifndef PHYSICSCOLLIDE_HPP
#define PHYSICSCOLLIDE_HPP

#include "PMath.hpp"
#include "PObject.hpp"
#include "PShape.hpp"
#include "PPoly.hpp"
#include "PCircle.hpp"

namespace Core
{
	class PCollide
	{

	public:
		static bool CollideObjects(const PObject& obj1, const PObject& obj2);

	private:
		static bool CollidePolys(const PObject& obj1, const PObject& obj2);
		static bool CollideCircles(const PObject& obj1, const PObject& obj2);
		static bool CollideCirclePoly(const PObject& obj1, const PObject& obj2);
	};
}


#endif
