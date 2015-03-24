#ifndef MPACK_POLYGON_HPP
#define MPACK_POLYGON_HPP

#include "Types.hpp"

#include "Math.hpp"

namespace MPACK
{
	namespace Algorithm
	{
		class Polygon
		{
		public:
			Polygon();
			~Polygon();



		protected:
			std::vector<Math::Vector2f> m_points;
		};
	}
}

#endif
