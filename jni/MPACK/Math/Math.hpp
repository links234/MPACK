#ifndef MPACK_MATH_HPP
#define MPACK_MATH_HPP

#include "Common.hpp"
#include "TransformState2.hpp"
#include "Matrix2.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Plane.hpp"
#include "Geom.hpp"
#include "AABB1D.hpp"
#include "AABB2D.hpp"

namespace MPACK
{
	namespace Math
	{
		typedef TransformState2<float>		TransformState2f;

		typedef Vector2<float> 				Vector2f;
		typedef Vector3<float> 				Vector3f;
		typedef Vector4<float> 				Vector4f;

		typedef Matrix2<float>				Matrix2f;
		typedef Matrix3<float> 				Matrix3f;
		typedef Matrix4<float> 				Matrix4f;

		typedef Plane<float>				Planef;

		typedef AABB1D<float>				AABB1Df;
		typedef AABB2D<float> 				AABB2Df;


		typedef TransformState2<double>		TransformState2d;

		typedef Vector2<double> 			Vector2d;
		typedef Vector3<double> 			Vector3d;
		typedef Vector4<double> 			Vector4d;

		typedef Matrix2<double>				Matrix2d;
		typedef Matrix3<double> 			Matrix3d;
		typedef Matrix4<double> 			Matrix4d;

		typedef Plane<double>				Planed;

		typedef AABB1D<double>				AABB1Dd;
		typedef AABB2D<double> 				AABB2Dd;
	}
}

#endif
