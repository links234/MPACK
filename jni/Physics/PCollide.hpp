#ifndef PHYSICSCOLLIDE_HPP
#define PHYSICSCOLLIDE_HPP

#include "PhysicsService.hpp"
#include "PObject.hpp"
#include "PShape.hpp"
#include "PPoly.hpp"

namespace Core
{
	bool CollideObjects(const PObject& obj1, const PObject& obj2);
}


#endif
