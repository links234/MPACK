#ifndef MPACK_AABB1DIMPLEMENTATION_HPP
#define MPACK_AABB1DIMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline Math::AABB1D<T>::AABB1D()
		: m_xmin(static_cast<T>(0)), m_xmax(static_cast<T>(0))
	{
	}

	template<class T> inline Math::AABB1D<T>::AABB1D(T xmin, T xmax)
		: m_xmin(xmin), m_xmax(xmax)
	{
	}

	template<class T> inline bool Math::AABB1D<T>::Intersect(const AABB1D<T> &other) const
	{
		if(m_xmax < other.m_xmin)
		{
			return false;
		}
		if(other.m_xmax < m_xmin)
		{
			return false;
		}
		return true;
	}

	template<class T> inline bool Math::AABB1D<T>::Contain(const T &point) const
	{
		if(m_xmax < point)
		{
			return false;
		}
		if(point < m_xmin)
		{
			return false;
		}
		return true;
	}

	template<class T> inline void Math::AABB1D<T>::Clear()
	{
		m_xmin = Misc<T>::c_Max;
		m_xmax = Misc<T>::c_Min;
	}

	template<class T> inline void Math::AABB1D<T>::AddPoint(const T &point)
	{
		if(point < m_xmin)
		{
			m_xmin = point;
		}
		if(point > m_xmax)
		{
			m_xmax = point;
		}
	}
}

#endif
