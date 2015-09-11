#ifndef MPACK_MATRIX2IMPLEMENTATION_HPP
#define MPACK_MATRIX2IMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> Math::Matrix2<T>::Matrix2()
		: m00(0), m01(0), m10(0), m11(0)
	{
	}

	template<class T> Math::Matrix2<T>::Matrix2(T radians)
	{
		T c = Misc<T>::Cos(radians);
		T s = Misc<T>::Sin(radians);

		m00 = c; m01 = -s;
		m10 = s; m11 =  c;
	}

	template<class T> Math::Matrix2<T>::Matrix2(T a, T b, T c, T d)
		: m00(a), m01(b), m10(c), m11(d)
	{
	}

	template<class T> void Math::Matrix2<T>::Set(T radians)
	{
		T c = Misc<T>::Cos(radians);
		T s = Misc<T>::Sin(radians);

		m00 = c; m01 = -s;
		m10 = s; m11 =  c;
	}

	template<class T> Math::Matrix2<T> Math::Matrix2<T>::Abs( void ) const
	{
		return Matrix2( Misc<T>::Abs( m00 ), Misc<T>::Abs( m01 ),
						Misc<T>::Abs( m10 ), Misc<T>::Abs( m11 ) );
	}

	template<class T> Math::Vector2<T> Math::Matrix2<T>::AxisX() const
	{
		return Vector2<T>(m00,m10);
	}

	template<class T> Math::Vector2<T> Math::Matrix2<T>::AxisY() const
	{
		return Vector2<T>(m01,m11);
	}

	template<class T> Math::Matrix2<T> Math::Matrix2<T>::Transpose() const
	{
		return Matrix2(m00,m10,m01,m11);
	}

	template<class T> const Math::Vector2<T> Math::Matrix2<T>::operator*(const Math::Vector2<T> &rhs ) const
	{
		return Vector2<T>(m00*rhs.x+m01*rhs.y, m10*rhs.x+m11*rhs.y);
	}

	template<class T> const Math::Matrix2<T> Math::Matrix2<T>::operator*(const Math::Matrix2<T> &rhs ) const
	{
		return Matrix2(
				m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
				m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
				m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
				m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		);
	}
}

#endif
