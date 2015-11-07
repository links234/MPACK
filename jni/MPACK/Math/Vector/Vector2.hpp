#ifndef MPACK_VECTOR2_HPP
#define MPACK_VECTOR2_HPP

#include "Common.hpp"
#include "Geom.hpp"

namespace MPACK
{
	namespace Math
	{
		template<class T> class Vector2
		{
		public:
			Vector2<T>(T x = static_cast<T>(0), T y = static_cast<T>(0)): x(x), y(y){};

			void Set(T x, T y);

			T SquareLength() const;
			T Length() const;
			T Magnitude() const;
			T Angle() const;
			T Distance(const Vector2<T> &point) const;
			T SquareDistance(const Vector2<T> &point) const;
			T Dot(const Vector2<T> &v) const;
			void Normalize();
			void SquareMap();
			void Rotate(T amount);
			Vector2<T>	Normalized();
			Vector2<T>	SquareMaped();
			Vector2<T>	Rotated(T amount);
			Vector2<T>	operator*	(const Vector2<T> &v) const;
			Vector2<T>	operator*	(const T &s) const;
			Vector2<T>	operator/	(const Vector2<T> &v) const;
			Vector2<T>	operator/	(const T &s) const;
			Vector2<T>	operator+	(const Vector2<T> &v) const;
			Vector2<T>	operator+	() const;
			Vector2<T>	operator-	(const Vector2<T> &v) const;
			Vector2<T>	operator-	() const;
			bool		operator!=	(const Vector2<T> &v) const;
			bool		operator==	(const Vector2<T> &v) const;
			Vector2<T>	operator+=	(const Vector2<T> &v);
			Vector2<T>	operator-=	(const Vector2<T> &v);
			Vector2<T>	operator*=	(const Vector2<T> &v);
			Vector2<T>	operator*=	(const T &s);
			Vector2<T>	operator/=	(const Vector2<T> &v);
			Vector2<T>	operator/=	(const T &s);

			T x;
			T y;
		};

		template<class T> Vector2<T> operator*(T s, const Vector2<T> &v);

		template<class T> Vector2<T> Cross(const Vector2<T> &v, T a);
		template<class T> Vector2<T> Cross(T a, const Vector2<T> &v);
		template<class T> T Cross(const Vector2<T> &a, const Vector2<T> &b );

		template<class T> Vector2<T> Dot(const Vector2<T> &v, T s);
		template<class T> Vector2<T> Dot(T s, const Vector2<T> &v);
		template<class T> T Dot(const Vector2<T> &a, const Vector2<T> &b);

		template<class T> T Distance(const Vector2<T> &a, const Vector2<T> &b);
		template<class T> T SquareDistance(const Vector2<T> &a, const Vector2<T> &b);
	}
}

#include "Vector2Implementation.hpp"

#endif
