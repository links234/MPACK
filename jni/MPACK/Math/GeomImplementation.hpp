#ifndef MPACK_GEOMIMPLEMENTATION_HPP
#define MPACK_GEOMIMPLEMENTATION_HPP

#include "AABB2D.hpp"

namespace MPACK
{
	template<class T> inline void Math::Geom<T>::CalculateTangentBitangent(const Math::Vector3<T> &P1, const Math::Vector3<T> &P2, const Math::Vector3<T> &P3, const Math::Vector2<T> &UV1, const Math::Vector2<T> &UV2, const Math::Vector2<T> &UV3, Math::Vector3<T> &tangent, Math::Vector3<T> &bitangent )
	{
		Math::Vector3<T> Edge1 = P2 - P1;
		Math::Vector3<T> Edge2 = P3 - P1;
		Math::Vector2<T> Edge1uv = UV2 - UV1;
		Math::Vector2<T> Edge2uv = UV3 - UV1;

		T cp = Edge1uv.y * Edge2uv.x - Edge1uv.x * Edge2uv.y;

		if ( cp != static_cast<T>(0) )
		{
			T mul = 1.0f / cp;
			tangent   = (Edge1 * -Edge2uv.y + Edge2 * Edge1uv.y) * mul;
			bitangent = (Edge1 * -Edge2uv.x + Edge2 * Edge1uv.x) * mul;

			tangent.Normalize();
			bitangent.Normalize();
		}
	}

	template<class T> inline bool Math::Geom<T>::SphereIntersectSphere(const Math::Vector3<T> &p1, const T &radius1, const Math::Vector3<T> &p2, const T &radius2)
	{
		return p1.Distance(p2)<=radius1+radius2;
	}

	template<class T> inline T Math::Geom<T>::TriangleDet2D(const Math::Vector2<T> &A, const Math::Vector2<T> &B, const Math::Vector2<T> &C)
	{
		return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
	}

	template<class T> inline void Math::Geom<T>::LineCoeff2D(const Math::Vector2<T> A, const Math::Vector2<T> B, T &a, T &b, T &c)
	{
		a=B.y-A.y;
		b=A.x-B.x;
		c=A.y*B.x-A.x*B.y;
	}

	template<class T> inline bool Math::Geom<T>::SegmentIntersect(const Math::Vector2<T> A1, const Math::Vector2<T> B1, const Math::Vector2<T> A2, const Math::Vector2<T> B2, Math::Vector2<T> &I)
	{
		if(Math::Misc<T>::Sign(TriangleDet2D(A1,B1,A2)) == Math::Misc<T>::Sign(TriangleDet2D(A1,B1,B2)))
		{
			return false;
		}
		if(Math::Misc<T>::Sign(TriangleDet2D(A2,B2,A1)) == Math::Misc<T>::Sign(TriangleDet2D(A2,B2,B1)))
		{
			return false;
		}
		if(!AABB2D<T>(A1,B1).Intersect(AABB2D<T>(A2,B2)))
		{
			return false;
		}
		T a1,b1,c1;
		LineCoeff2D(A1,B1,a1,b1,c1);
		T a2,b2,c2;
		LineCoeff2D(A2,B2,a2,b2,c2);
		I.x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
		I.y=(c1*a2-c2*a1)/(a1*b2-a2*b1);
		return true;
	}

	template<class T> inline bool Math::Geom<T>::LineIntersect(const Vector2<T> &A1, const Vector2<T> &B1, const Vector2<T> &A2, const Vector2<T> &B2, Vector2<T> &I)
	{
		if ( (B1.y - A1.y) * (B2.x - A2.x) == (B2.y - A2.y) * (B1.x - A1.x) )
		{
			return false;
		}
		T a1,b1,c1;
		LineCoeff2D(A1,B1,a1,b1,c1);
		T a2,b2,c2;
		LineCoeff2D(A2,B2,a2,b2,c2);
		I.x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
		I.y=(c1*a2-c2*a1)/(a1*b2-a2*b1);
		return true;
	}
}

#endif
