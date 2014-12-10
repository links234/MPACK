#ifndef MPACK_PHYSICSSHAPE_HPP
#define MPACK_PHYSICSSHAPE_HPP

#include "PMath.hpp"

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

		PShape();
		virtual ~PShape();

		virtual void ComputeAABB(PAABB* p_aabb, PVec2 p_translate, float p_angle) const = 0;

		const Type GetType() const;

		Type m_type;
	};

	inline const PShape::Type PShape::GetType() const { return m_type; }
}

#endif
