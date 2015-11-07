#ifndef MPACK_VECTOR4_HPP
#define MPACK_VECTOR4_HPP

namespace MPACK
{
	namespace Math
	{
		template<class T> class Vector4
		{
		public:
			Vector4<T>(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0), T w = static_cast<T>(0)): x(x), y(y), z(z), w(w){};

			T Length() const;
			T Magnitude() const;
			T Distance(const Vector4<T> &point) const;
			T Dot(const Vector4<T> &v) const;
			void Normalize();
			Vector4<T>	Normalized();
			Vector4<T>	operator*	(const Vector4<T> &v) const;
			Vector4<T>	operator*	(const T &s) const;
			Vector4<T>	operator/	(const Vector4<T> &v) const;
			Vector4<T>	operator/	(const T &s) const;
			Vector4<T>	operator+	(const Vector4<T> &v) const;
			Vector4<T>	operator-	(const Vector4<T> &v) const;
			bool		operator!=	(const Vector4<T> &v) const;
			bool		operator==	(const Vector4<T> &v) const;
			Vector4<T>	operator+=	(const Vector4<T> &v);
			Vector4<T>	operator-=	(const Vector4<T> &v);
			Vector4<T>	operator*=	(const Vector4<T> &v);
			Vector4<T>	operator*=	(const T &s);
			Vector4<T>	operator/=	(const Vector4<T> &v);
			Vector4<T>	operator/=	(const T &s);

			T x;
			T y;
			T z;
			T w;
		};
	}
}

#include "Vector4Implementation.hpp"

#endif
