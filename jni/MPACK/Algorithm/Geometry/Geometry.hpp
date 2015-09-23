#ifndef MPACK_GEOMETRY_HPP
#define MPACK_GEOMETRY_HPP

#include "Types.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Algorithm
	{
		float Cross(const Math::Vector2f &O, const Math::Vector2f &A, const Math::Vector2f &B);
		std::vector<Math::Vector2f> ConvexHull(std::vector<Math::Vector2f> points);

		std::vector<Math::Vector2f>& ClipPolygon(const std::vector<Math::Vector2f>& clip, std::vector<Math::Vector2f> polygon, std::vector<Math::Vector2f>& result);
		float PolygonArea(const std::vector <Math::Vector2f> & polygon);
	}
}

#endif
