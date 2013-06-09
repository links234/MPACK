/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef AABB1D_HPP
#define AABB1D_HPP

namespace Math
{
	template<class T> class AABB1D
	{
	public:
		AABB1D<T>();
		AABB1D<T>(T xmin, T xmax);

		bool Intersect(const AABB1D<T> &r) const;
		bool Contain(const T &p) const;

		void Clear();
		void AddPoint(const T &p);

		T xmin,xmax;
	};
	
	template<class T> inline AABB1D<T>::AABB1D()
		: xmin(static_cast<T>(0)), xmax(static_cast<T>(0))
	{
	}

	template<class T> inline AABB1D<T>::AABB1D(T xmin, T xmax)
		: xmin(xmin), xmax(xmax)
	{
	}

	template<class T> inline bool AABB1D<T>::Intersect(const AABB1D<T> &r) const
	{
		if(xmax<r.xmin)
		{
			return false;
		}
		if(r.xmax<xmin)
		{
			return false;
		}
		return true;
	}

	template<class T> inline bool AABB1D<T>::Contain(const T &p) const
	{
		if(xmax<p)
		{
			return false;
		}
		if(p<xmin)
		{
			return false;
		}
		return true;
	}

	template<class T> inline void AABB1D<T>::Clear()
	{
		xmin=Misc<T>::c_Max;
		xmax=Misc<T>::c_Min;
	}

	template<class T> inline void AABB1D<T>::AddPoint(const T &p)
	{
		if(p<xmin)
		{
			xmin=p;
		}
		if(p>xmax)
		{
			xmax=p;
		}
	}
}

#endif
