#ifndef MPACK_SHAPE_HPP
#define MPACK_SHAPE_HPP

#include "Types.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Physics
	{
		class Body;
	}
}

namespace MPACK
{
	namespace Physics
	{
		class Shape
		{
		public:
			enum Type
			{
				eCircle,
				ePoly,
				eCount
			};

			Shape();
			virtual Shape *Clone() const = 0;
			virtual void Initialize() = 0;
			virtual void ComputeMass(float density) = 0;
			virtual void SetOrientation(float radians) = 0;
			virtual Type GetType() const = 0;
			virtual void ComputeAABB() = 0;

			Body *body;
			Math::AABB2Df m_aabb;
		};
	}
}

#endif
