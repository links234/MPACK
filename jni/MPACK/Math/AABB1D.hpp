#ifndef MPACK_AABB1D_HPP
#define MPACK_AABB1D_HPP

namespace MPACK
{
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
}

#include "AABB1DImplementation.hpp"

#endif
