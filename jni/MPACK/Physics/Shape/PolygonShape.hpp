#ifndef MPACK_POLYGONSHAPE_HPP
#define MPACK_POLYGONSHAPE_HPP

#include "Shape.hpp"

#define POLYGONSHAPE_MAXVERTEXCOUNT 64

namespace MPACK
{
	namespace Physics
	{
		class PolygonShape : public Shape
		{
		public:
			PolygonShape();

			void Initialize();
			Shape *Clone() const;
			void ComputeMass(float density);
			void SetOrientation(float radians);
			Type GetType() const;
			void ComputeAABB();

			void SetAsBox(float hw,float hh);
			void Set(MPACK::Math::Vector2f *vertices, int count);

			MPACK::Math::Vector2f GetSupport(const MPACK::Math::Vector2f& dir);

			int m_vertexCount;
			MPACK::Math::Vector2f m_vertices[POLYGONSHAPE_MAXVERTEXCOUNT];
			MPACK::Math::Vector2f m_normals[POLYGONSHAPE_MAXVERTEXCOUNT];

			MPACK::Math::Matrix2f u;
		};
	}
}

#endif
