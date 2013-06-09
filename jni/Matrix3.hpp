/*
	This file is owned by Murtaza Alexandru and may not be distributed, edited or used without written permission of the owner
	When using this work you accept to keep this header
	E-mails from murtaza_alexandru73@yahoo.com with permissions can be seen as valid.
*/



#ifndef MATRIX3_HPP
#define MATRIX3_HPP

#include "Matrix4.hpp"

namespace Math
{
	template<class T> class Matrix3
	{
	public:
		T m_matrix[3][3];

		static void CalculateNormalMatrix(Matrix3<T> &matrix, Matrix4<T> &modelviewMatrix);
	};

	template<class T> inline void Matrix3<T>::CalculateNormalMatrix(Matrix3<T> &matrix, Matrix4<T> &modelviewMatrix)
	{
		//Grab the top 3x3 of the modelview matrix
		T M[9];
		M[0] = modelviewMatrix.m_matrix[0][0];
		M[1] = modelviewMatrix.m_matrix[1][0];
		M[2] = modelviewMatrix.m_matrix[2][0];
		M[3] = modelviewMatrix.m_matrix[0][1];
		M[4] = modelviewMatrix.m_matrix[1][1];
		M[5] = modelviewMatrix.m_matrix[2][1];
		M[6] = modelviewMatrix.m_matrix[0][2];
		M[7] = modelviewMatrix.m_matrix[1][2];
		M[8] = modelviewMatrix.m_matrix[2][2];

		//Work out the determinate
		T determinate = M[0] * M[4] * M[8] + M[1] * M[5] * M[6] + M[2] * M[3] * M[7];
		determinate -= M[2] * M[4] * M[6] + M[0] * M[5] * M[7] + M[1] * M[3] * M[8];

		//One division is faster than several
		T oneOverDet = 1.0f / determinate;

		//Calculate the inverse and assign it to the transpose matrix positions
		matrix.m_matrix[0][0] = (M[4] * M[8] - M[5] * M[7]) * oneOverDet;
		matrix.m_matrix[0][1] = (M[2] * M[7] - M[1] * M[8]) * oneOverDet;
		matrix.m_matrix[0][2] = (M[1] * M[5] - M[2] * M[4]) * oneOverDet;

		matrix.m_matrix[1][0] = (M[5] * M[6] - M[3] * M[8]) * oneOverDet;
		matrix.m_matrix[1][1] = (M[0] * M[8] - M[2] * M[6]) * oneOverDet;
		matrix.m_matrix[1][2] = (M[2] * M[3] - M[0] * M[5]) * oneOverDet;

		matrix.m_matrix[2][0] = (M[3] * M[7] - M[4] * M[6]) * oneOverDet;
		matrix.m_matrix[2][1] = (M[1] * M[6] - M[8] * M[7]) * oneOverDet;
		matrix.m_matrix[2][2] = (M[0] * M[4] - M[1] * M[3]) * oneOverDet;
	}
}

#endif
