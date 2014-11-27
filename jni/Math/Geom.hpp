/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef GEOM_HPP
#define GEOM_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace Math
{
	template<class T> class Vector2;
	template<class T> class Vector3;

	template<class T> class Geom
	{
	public:
		static void CalculateTangentBitangent(const Vector3<T> &P1, const Vector3<T> &P2, const Vector3<T> &P3, const Vector2<T> &UV1, const Vector2<T> &UV2, const Vector2<T> &UV3, Vector3<T> &tangent, Vector3<T> &bitangent );

		static bool SphereIntersectSphere(const Vector3<T> &p1, const T &radius1, const Vector3<T> &p2, const T &radius2);

		static T TriangleDet2D(const Vector2<T> &A, const Vector2<T> &B, const Vector2<T> &C);

		static void LineCoeff2D(const Vector2<T> A, const Vector2<T> B, T &a, T &b, T &c);

		static bool LineIntersect(const Vector2<T> A1, const Vector2<T> B1, const Vector2<T> A2, const Vector2<T> B2, Vector2<T> &I);
	};
}

#include "GeomImplementation.hpp"

#endif
