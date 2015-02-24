#ifndef MPACK_PMATH_HPP
#define MPACK_PMATH_HPP

#include "Vector2.hpp"
#include "AABB1D.hpp"
#include "AABB2D.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Physics
	{
		typedef Math::Vector2<float> 	PVec2;
		typedef Math::AABB2D<float> 		PAABB;
		typedef Math::AABB1D<float> 		PSegm;
	}
}

#endif
