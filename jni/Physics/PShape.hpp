#ifndef PHYSICSSHAPE_HPP
#define PHYSICSSHAPE_HPP

#include "PhysicsService.hpp"

namespace Core
{
	class PShape
	{
	public:
		enum Type
		{
			e_poly,
			e_circle
		};

		virtual void ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle) = 0;

		Type GetType();

		Type m_type;
	};
}

#endif
