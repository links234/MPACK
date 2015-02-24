#ifndef MPACK_AABB2DIMPLEMENTATION_HPP
#define MPACK_AABB2DIMPLEMENTATION_HPP

namespace MPACK
{
	template<class T> inline Math::AABB2D<T>::AABB2D()
		: m_xmin(static_cast<T>(0)), m_xmax(static_cast<T>(0)), m_ymin(static_cast<T>(0)), m_ymax(static_cast<T>(0))
	{
	}

	template<class T> inline Math::AABB2D<T>::AABB2D(Math::AABB1D<T> x, Math::AABB1D<T> y)
		: m_xmin(x.xmin), m_xmax(x.xmax), m_ymin(y.xmin), m_ymax(y.xmax)
	{
	}

	template<class T> inline Math::AABB2D<T>::AABB2D(Math::Vector2<T> A, Math::Vector2<T> B)
	{
		if(A.x < B.x)
		{
			m_xmin = A.x;
			m_xmax = B.x;
		}
		else
		{
			m_xmin = B.x;
			m_xmax = A.x;
		}
		if(A.y < B.y)
		{
			m_ymin = A.y;
			m_ymax = B.y;
		}
		else
		{
			m_ymin = B.y;
			m_ymax = A.y;
		}
	}

	template<class T> inline Math::AABB2D<T>::AABB2D(T xmin, T xmax, T ymin, T ymax)
		: m_xmin(xmin), m_xmax(xmax), m_ymin(ymin), m_ymax(ymax)
	{
	}

	template<class T> inline bool Math::AABB2D<T>::Intersect(const Math::AABB2D<T> &other) const
	{
		return Math::AABB1D<T>(other.m_xmin,other.m_xmax).Intersect(Math::AABB1D<T>(m_xmin,m_xmax)) && Math::AABB1D<T>(other.m_ymin,other.m_ymax).Intersect(Math::AABB1D<T>(m_ymin,m_ymax));
	}

	template<class T> inline bool Math::AABB2D<T>::Contain(const Math::Vector2<T> &point) const
	{
		return Math::AABB1D<T>(m_xmin,m_xmax).Contain(point.x) && Math::AABB1D<T>(m_ymin,m_ymax).Contain(point.y);
	}

	template<class T> inline void Math::AABB2D<T>::Clear()
	{
		m_xmin = m_ymin = Math::Misc<T>::c_Max;
		m_xmax = m_ymax = Math::Misc<T>::c_Min;
	}

	template<class T> inline void Math::AABB2D<T>::AddPoint(const Math::Vector2<T> &point)
	{
		if(point.x < m_xmin)
		{
			m_xmin = point.x;
		}
		if(point.x > m_xmax)
		{
			m_xmax = point.x;
		}
		if(point.y < m_ymin)
		{
			m_ymin = point.y;
		}
		if(point.y > m_ymax)
		{
			m_ymax = point.y;
		}
	}
}

#endif
