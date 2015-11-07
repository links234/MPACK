#ifndef MPACK_MATRIX2_HPP
#define MPACK_MATRIX2_HPP

#include "Vector2.hpp"

namespace MPACK
{
	namespace Math
	{
		template<class T> class Matrix2
		{
		public:
			union
			{
				struct
				{
					T m00, m01;
					T m10, m11;
				};

				T m[2][2];
				T v[4];
			};

			Matrix2();
			Matrix2(T radians);
			Matrix2(T a, T b, T c, T d);

			void Set(T radians);

			Matrix2<T> Abs( void ) const;

			Vector2<T> AxisX() const;
			Vector2<T> AxisY() const;

			Matrix2 Transpose() const;

			const Vector2<T> operator*(const Vector2<T> &rhs ) const;
			const Matrix2 operator*(const Matrix2 &rhs ) const;
		};
	}
}

#include "Matrix2Implementation.hpp"

#endif
