#ifndef MPACK_COLLISIONINFO_HPP
#define MPACK_COLLISIONINFO_HPP

#include "Math.hpp"

namespace MPACK
{
	namespace Physics
	{
		class CollisionInfo
		{
		public:
			float penetration;
			MPACK::Math::Vector2f normal;
			MPACK::Math::Vector2f contacts[2];
			int contactCount;
		};
	}
}

#endif
