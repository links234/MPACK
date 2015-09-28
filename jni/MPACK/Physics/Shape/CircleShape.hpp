#ifndef MPACK_CIRCLESHAPE_HPP
#define MPACK_CIRCLESHAPE_HPP

#include "Shape.hpp"

namespace MPACK
{
	namespace Physics
	{
		class CircleShape : public Shape
		{
		public:
			CircleShape(float r);

			Shape *Clone() const;
			void Initialize();
			void ComputeMass(float density);
			void SetOrientation(float radians);
			Type GetType() const;
			void ComputeAABB();

			float radius;
		};
	}
}

#endif
