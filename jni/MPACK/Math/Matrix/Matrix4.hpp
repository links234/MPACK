#ifndef MPACK_MATRIX4_HPP
#define MPACK_MATRIX4_HPP

namespace MPACK
{
	namespace Math
	{
		template<class T> class Vector3;

		template<class T> class Matrix4
		{
		public:
			Matrix4<T> operator* (const Matrix4<T> &matrix) const;

			static void SetIdentity(Matrix4<T> &matrix);

			static void SetScale(Matrix4<T> &matrix, T x=static_cast<T>(1), T y=static_cast<T>(1), T z=static_cast<T>(1));
			static void SetTrans(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetRoll(Matrix4<T> &matrix, T angle=static_cast<T>(0));
			static void SetPitch(Matrix4<T> &matrix, T angle=static_cast<T>(0));
			static void SetYaw(Matrix4<T> &matrix, T angle=static_cast<T>(0));
			static void SetRotationXYZ(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetRotationXZY(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetRotationYXZ(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetRotationYZX(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetRotationZXY(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetRotationZYX(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetAxisRotation(Matrix4<T> &matrix, Vector3<T> axis, T angle=static_cast<T>(0));

			static void SetInverseScale(Matrix4<T> &matrix, T x=static_cast<T>(1), T y=static_cast<T>(1), T z=static_cast<T>(1));
			static void SetInverseTrans(Matrix4<T> &matrix, T x=static_cast<T>(1), T y=static_cast<T>(1), T z=static_cast<T>(1));
			static void SetInverseRoll(Matrix4<T> &matrix, T angle=static_cast<T>(0));
			static void SetInversePitch(Matrix4<T> &matrix, T angle=static_cast<T>(0));
			static void SetInverseYaw(Matrix4<T> &matrix, T angle=static_cast<T>(0));
			static void SetInverseRotationXYZ(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetInverseRotationXZY(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetInverseRotationYXZ(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetInverseRotationYZX(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetInverseRotationZXY(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetInverseRotationZYX(Matrix4<T> &matrix, T x=static_cast<T>(0), T y=static_cast<T>(0), T z=static_cast<T>(0));
			static void SetInverseAxisRotation(Matrix4<T> &matrix, Vector3<T> axis, T angle=static_cast<T>(0));

			static void SetOrtho(Matrix4<T> &matrix, T l, T r, T b, T t, T n,T f);
			static void SetFrustum(Matrix4<T> &matrix, T l, T r, T b, T t, T n, T f);
			static void SetPerspective(Matrix4<T> &matrix, T fov, T aspect, T n, T f);

			static void SetCamera(Matrix4<T> &matrix, Vector3<T> look, Vector3<T> up, Vector3<T> right, Vector3<T> position);
			static void SetObject(Matrix4<T> &matrix, Vector3<T> look, Vector3<T> up, Vector3<T> right, Vector3<T> position);

			static void Transpose(Matrix4<T> &matrix);
			static void Inverse(Matrix4<T> &matrix);

			T m_matrix[4][4];
		};
	}
}

#include "Matrix4Implementation.hpp"
	
#endif
