#ifndef MPACK_AABB2D_HPP
#define MPACK_AABB2D_HPP

#include "AABB1D.hpp"
#include "Vector2.hpp"

namespace MPACK
{
	namespace Math
	{
		template<class T> class AABB2D
		{
		public:
			AABB2D();
			AABB2D(AABB1D<T> x, AABB1D<T> y);
			AABB2D(Vector2<T> A, Vector2<T> B);
			AABB2D(T xmin, T xmax, T ymin, T ymax);

			bool Intersect(const AABB2D<T> &other) const;
			bool Contain(const Vector2<T> &point) const;
	
			void Clear();
			void AddPoint(const Vector2<T> &point);

			T m_xmin, m_xmax, m_ymin, m_ymax;
		};
	}
}

#include "AABB2DImplementation.hpp"

#endif
