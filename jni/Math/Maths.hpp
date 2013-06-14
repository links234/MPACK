/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MATHS_HPP
#define MATHS_HPP

#include "Common.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Plane.hpp"
#include "Geom.hpp"
#include "AABB1D.hpp"
#include "AABB2D.hpp"

namespace Math
{
	typedef Vector2<float> 	Vector2f;
	typedef Vector3<float> 	Vector3f;
	typedef Vector4<float> 	Vector4f;

	typedef Matrix3<float> 	Matrix3f;
	typedef Matrix4<float> 	Matrix4f;

	typedef Plane<float>	Planef;

	typedef AABB1D<float>	AABB1Df;
	typedef AABB2D<float> 	AABB2Df;
}

#endif
