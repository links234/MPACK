/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef AABB2D_HPP
#define AABB2D_HPP

#include "AABB1D.hpp"
#include "Vector2.hpp"

namespace Math
{
	template<class T> class AABB2D
	{
	public:
		AABB2D();
		AABB2D(AABB1D<T> x, AABB1D<T> y);
		AABB2D(Vector2<T> A, Vector2<T> B);
		AABB2D(T xmin, T xmax, T ymin, T ymax);

		bool Intersect(const AABB2D<T> &r) const;
		bool Contain(const Vector2<T> &p) const;

		void Clear();
		void AddPoint(const Vector2<T> &p);
	
		T xmin,xmax,ymin,ymax;
	};
	
	template<class T> inline AABB2D<T>::AABB2D()
		: xmin(static_cast<T>(0)), xmax(static_cast<T>(0)), ymin(static_cast<T>(0)), ymax(static_cast<T>(0))
	{
	}

	template<class T> inline AABB2D<T>::AABB2D(AABB1D<T> x, AABB1D<T> y)
		: xmin(x.xmin), xmax(x.xmax), ymin(y.xmin), ymax(y.xmax)
	{
	}

	template<class T> inline AABB2D<T>::AABB2D(Vector2<T> A, Vector2<T> B)
	{
		if(A.x<B.x)
		{
			xmin=A.x;
			xmax=B.x;
		}
		else
		{
			xmin=B.x;
			xmax=A.x;
		}
		if(A.y<B.y)
		{
			ymin=A.y;
			ymax=B.y;
		}
		else
		{
			ymin=B.y;
			ymax=A.y;
		}
	}

	template<class T> inline AABB2D<T>::AABB2D(T xmin, T xmax, T ymin, T ymax)
		: xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax)
	{
	}

	template<class T> inline bool AABB2D<T>::Intersect(const AABB2D<T> &r) const
	{
		return AABB1D<T>(r.xmin,r.xmax).Intersect(AABB1D<T>(xmin,xmax)) && AABB1D<T>(r.ymin,r.ymax).Intersect(AABB1D<T>(ymin,ymax));
	}

	template<class T> inline bool AABB2D<T>::Contain(const Vector2<T> &p) const
	{
		return AABB1D<T>(xmin,xmax).Contain(p.x) && AABB1D<T>(ymin,ymax).Contain(p.y);
	}

	template<class T> inline void AABB2D<T>::Clear()
	{
		xmin=ymin=Misc<T>::c_Max;
		xmax=ymax=Misc<T>::c_Min;
	}

	template<class T> inline void AABB2D<T>::AddPoint(const Vector2<T> &p)
	{
		if(p.x<xmin)
		{
			xmin=p.x;
		}
		if(p.x>xmax)
		{
			xmax=p.x;
		}
		if(p.y<ymin)
		{
			ymin=p.y;
		}
		if(p.y>ymax)
		{
			ymax=p.y;
		}
	}
}

#endif
