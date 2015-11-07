#ifndef MPACK_MATRIX3_HPP
#define MPACK_MATRIX3_HPP

#include "Matrix4.hpp"

namespace MPACK
{
	namespace Math
	{
		template<class T> class Matrix3
		{
		public:
			T m_matrix[3][3];

			static void CalculateNormalMatrix(Matrix3<T> &matrix, Matrix4<T> &modelviewMatrix);
		};
	}
}

#include "Matrix3Implementation.hpp"

#endif
