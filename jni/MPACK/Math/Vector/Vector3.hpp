#ifndef MPACK_VECTOR3_HPP
#define MPACK_VECTOR3_HPP

namespace MPACK
{
	namespace Math
	{
		template<class T> class Matrix4;

		template<class T> class Vector3
		{
		public:
			Vector3(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0)): x(x), y(y), z(z){};

			T Length() const;
			T Magnitude() const;
			T Distance(const Vector3<T> &point) const;
			T Dot(const Vector3<T> &v) const;
			void		Normalize();
			Vector3<T>	Normalized();
			Vector3<T>	Cross		(const Vector3<T> &v) const;
			Vector3<T>	operator*	(const Matrix4<T> &m) const;
			Vector3<T>	operator*	(const Vector3<T> &v) const;
			Vector3<T>	operator*	(const T &s) const;
			Vector3<T>	operator/	(const Vector3<T> &v) const;
			Vector3<T>	operator/	(const T &s) const;
			Vector3<T>	operator+	(const Vector3<T> &v) const;
			Vector3<T>	operator-	(const Vector3<T> &v) const;
			bool		operator!=	(const Vector3<T> &v) const;
			bool		operator==	(const Vector3<T> &v) const;
			Vector3<T>	operator+=	(const Vector3<T> &v);
			Vector3<T>	operator-=	(const Vector3<T> &v);
			Vector3<T>	operator*=	(const Matrix4<T> &m);
			Vector3<T>	operator*=	(const Vector3<T> &v);
			Vector3<T>	operator*=	(const T &s);
			Vector3<T>	operator/=	(const Vector3<T> &v);
			Vector3<T>	operator/=	(const T &s);

			T x;
			T y;
			T z;
		};
	}
}

#include "Vector3Implementation.hpp"

#endif
