/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MPACK_MATRIX3_HPP
#define MPACK_MATRIX3_HPP

#include "Matrix4.hpp"

namespace Math
{
	template<class T> class Matrix3
	{
	public:
		T m_matrix[3][3];

		static void CalculateNormalMatrix(Matrix3<T> &matrix, Matrix4<T> &modelviewMatrix);
	};
}

#include "Matrix3Implementation.hpp"

#endif
