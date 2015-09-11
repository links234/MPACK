#ifndef MPACK_COLLIDER_HPP
#define MPACK_COLLIDER_HPP

#include "Shape.hpp"
#include "Math.hpp"

namespace MPACK
{
	namespace Physics
	{
		class Manifold;
		class Body;
		class PolygonShape;
		class CircleShape;
	}
}

namespace MPACK
{
	namespace Physics
	{
		class Collider
		{
		public:
			typedef void (*Callback)(Manifold *m,Body *a,Body *b);

			static Callback Dispatch[Shape::eCount][Shape::eCount];

			static void CircleToCircle(Manifold *m,Body *a,Body *b);
			static void CircleToPolygon(Manifold *m,Body *a,Body *b);
			static void PolygonToCircle(Manifold *m,Body *a,Body *b);
			static void PolygonToPolygon(Manifold *m,Body *a,Body *b);

		private:
			static float FindAxisLeastPenetration(int *faceIndex,PolygonShape *A,PolygonShape *B);
			static void FindIncidentFace(MPACK::Math::Vector2f *v,PolygonShape *RefPoly,PolygonShape *IncPoly,int referenceIndex);
			static int Clip(MPACK::Math::Vector2f n,float c,MPACK::Math::Vector2f *face);
		};
	}
}

#endif
