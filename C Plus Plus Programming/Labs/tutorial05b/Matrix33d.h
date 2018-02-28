#pragma once

//-----------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include "Vector3d.h"

#define M33_EPSILON 1.0E-8

/**
* Double precision, 3x3 matrix class.
*/

class Matrix33d
{
	public:
		Matrix33d();
		Matrix33d(double matrix[9]);

		const Vector3d GetElement(const Matrix33d &matrix, const int element) const;

		Matrix33d Transpose(const Matrix33d &matrix) const;

		Matrix33d Add(const Matrix33d &matrix) const;

		const Matrix33d operator + (const Matrix33d &matrix) const
		{
			return Add(matrix);
		}

		Matrix33d Subtract(const Matrix33d &matrix) const;

		const Matrix33d operator - (const Matrix33d &matrix) const
		{
			return Subtract(matrix);
		}

		Matrix33d Multiply(const double n) const;

		const Vector3d Multiply(const Vector3d &vector) const;

		Matrix33d Multiply(const Matrix33d &matrix) const;

		const Matrix33d operator * (const double n) const
		{
			return Multiply(n);
		}

		const Vector3d operator * (const Vector3d &vector) const
		{
			return Multiply(vector);
		}

		const Matrix33d operator * (const Matrix33d &matrix) const
		{
			return Multiply(matrix);
		}

	private:
		Vector3d m_row[3]; // rows
};

ostream &operator << (ostream &stream, const Matrix33d &matrix);

istream &operator >> (istream &stream, Matrix33d &matrix);

Matrix33d operator - (const Matrix33d &vector);