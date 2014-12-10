/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_VECTOR2_HPP
#define MPACK_VECTOR2_HPP

#include "Common.hpp"
#include "Geom.hpp"

namespace Math
{
	template<class T> class Vector2
	{
	public:
		Vector2<T>(T x = static_cast<T>(0), T y = static_cast<T>(0)): x(x), y(y){};

		T Length() const;
		T Magnitude() const;
		T Angle() const;
		T Distance(const Vector2<T> &point) const;
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
		Vector2<T>	operator-	(const Vector2<T> &v) const;
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
}

#include "Vector2Implementation.hpp"

#endif
