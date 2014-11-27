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

		bool Intersect(const AABB1D<T> &other) const;
		bool Contain(const T &point) const;

		void Clear();
		void AddPoint(const T &point);

		T m_xmin, m_xmax;
	};
}

#include "AABB1DImplementation.hpp"

#endif
