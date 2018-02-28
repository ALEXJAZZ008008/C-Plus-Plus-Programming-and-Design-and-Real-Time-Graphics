#include <cmath>

#include "Matrix33d.h"

//-----------------------------------------------------------------------------

Matrix33d::Matrix33d()
{

}

//-----------------------------------------------------------------------------

Matrix33d::Matrix33d(double matrix[9])
{
	m_row[0].x = matrix[0]; m_row[0].y = matrix[1]; m_row[0].z = matrix[2];
	m_row[1].x = matrix[3]; m_row[1].y = matrix[4]; m_row[1].z = matrix[5];
	m_row[2].x = matrix[6]; m_row[2].y = matrix[7]; m_row[2].z = matrix[8];
}

//-----------------------------------------------------------------------------

const Vector3d Matrix33d::GetElement(const Matrix33d &matrix, const int element) const
{
	return matrix.m_row[element];
}

Matrix33d Matrix33d::Transpose(const Matrix33d &inMatrix) const
{
	double matrix[9];

	matrix[0] = GetElement(inMatrix, 0).x;
	matrix[1] = GetElement(inMatrix, 1).x;
	matrix[2] = GetElement(inMatrix, 2).x;
	matrix[3] = GetElement(inMatrix, 0).y;
	matrix[4] = GetElement(inMatrix, 1).y;
	matrix[5] = GetElement(inMatrix, 2).y;
	matrix[6] = GetElement(inMatrix, 0).z;
	matrix[7] = GetElement(inMatrix, 1).z;
	matrix[8] = GetElement(inMatrix, 2).z;

	return Matrix33d(matrix);
}

Matrix33d Matrix33d::Add(const Matrix33d &inMatrix) const
{
	double matrix[9];

	for (int i = 0; i < 3; i++)
	{
		matrix[i * 3] = GetElement(*this, i).x + GetElement(inMatrix, i).x;
		matrix[(i * 3) + 1] = GetElement(*this, i).y + GetElement(inMatrix, i).y;
		matrix[(i * 3) + 2] = GetElement(*this, i).z + GetElement(inMatrix, i).z;
	}

	return Matrix33d(matrix);
}

Matrix33d Matrix33d::Subtract(const Matrix33d &inMatrix) const
{
	double matrix[9];

	for (int i = 0; i < 3; i++)
	{
		matrix[i * 3] = GetElement(*this, i).x - GetElement(inMatrix, i).x;
		matrix[(i * 3) + 1] = GetElement(*this, i).y - GetElement(inMatrix, i).y;
		matrix[(i * 3) + 2] = GetElement(*this, i).z - GetElement(inMatrix, i).z;
	}

	return Matrix33d(matrix);
}

Matrix33d Matrix33d::Multiply(const double n) const
{
	double matrix[9];

	for (int i = 0; i < 3; i++)
	{
		matrix[i * 3] = GetElement(*this, i).x * n;
		matrix[(i * 3) + 1] = GetElement(*this, i).y * n;
		matrix[(i * 3) + 2] = GetElement(*this, i).z * n;
	}

	return Matrix33d(matrix);
}

const Vector3d Matrix33d::Multiply(const Vector3d &vector) const
{
	return Vector3d((vector.x * GetElement(*this, 0).x) + (vector.x * GetElement(*this, 0).y) + (vector.x * GetElement(*this, 0).z), (vector.y * GetElement(*this, 1).x) + (vector.y * GetElement(*this, 1).y) + (vector.y * GetElement(*this, 1).z), (vector.z * GetElement(*this, 2).x) + (vector.z * GetElement(*this, 2).y) + (vector.z * GetElement(*this, 2).z));
}

Matrix33d Matrix33d::Multiply(const Matrix33d &inMatrix) const
{
	Matrix33d temporaryMatrix = Transpose(inMatrix);

	double matrix[9];

	for (int i = 0; i < 3; i++)
	{
		matrix[i * 3] = GetElement(*this, i).x * GetElement(temporaryMatrix, i).x;
		matrix[(i * 3) + 1] = GetElement(*this, i).y * GetElement(temporaryMatrix, i).y;
		matrix[(i * 3) + 2] = GetElement(*this, i).z * GetElement(temporaryMatrix, i).z;
	}

	return Matrix33d(matrix);
}

ostream &operator << (ostream &stream, const Matrix33d &matrix)
{
	for (int i = 0; i < 3; i++)
	{
		stream << matrix.GetElement(matrix, i).x << " " << matrix.GetElement(matrix, i).y << " " << matrix.GetElement(matrix, i).z << endl;
	}

	return stream;
}

istream &operator >> (istream &stream, Matrix33d &outMatrix)
{
	double matrix[9];

	for (int i = 0; i < 9; i++)
	{
		cin >> matrix[i];
	}

	outMatrix = Matrix33d(matrix);

	return stream;
}

Matrix33d operator - (const Matrix33d &inMatrix)
{
	double matrix[9];

	matrix[0] = (inMatrix.GetElement(inMatrix, 1).y * inMatrix.GetElement(inMatrix, 2).z) - (inMatrix.GetElement(inMatrix, 2).y * inMatrix.GetElement(inMatrix, 1).z);
	matrix[1] = (inMatrix.GetElement(inMatrix, 1).x * inMatrix.GetElement(inMatrix, 2).z) - (inMatrix.GetElement(inMatrix, 1).z * inMatrix.GetElement(inMatrix, 2).x);
	matrix[2] = (inMatrix.GetElement(inMatrix, 1).x * inMatrix.GetElement(inMatrix, 2).y) - (inMatrix.GetElement(inMatrix, 1).y * inMatrix.GetElement(inMatrix, 2).x);
	matrix[3] = (inMatrix.GetElement(inMatrix, 0).y * inMatrix.GetElement(inMatrix, 2).z) - (inMatrix.GetElement(inMatrix, 0).z * inMatrix.GetElement(inMatrix, 2).y);
	matrix[4] = (inMatrix.GetElement(inMatrix, 0).x * inMatrix.GetElement(inMatrix, 2).z) - (inMatrix.GetElement(inMatrix, 0).z * inMatrix.GetElement(inMatrix, 2).x);
	matrix[5] = (inMatrix.GetElement(inMatrix, 0).x * inMatrix.GetElement(inMatrix, 2).y) - (inMatrix.GetElement(inMatrix, 0).y * inMatrix.GetElement(inMatrix, 2).x);
	matrix[6] = (inMatrix.GetElement(inMatrix, 0).y * inMatrix.GetElement(inMatrix, 1).z) - (inMatrix.GetElement(inMatrix, 1).y * inMatrix.GetElement(inMatrix, 0).z);
	matrix[7] = (inMatrix.GetElement(inMatrix, 0).x * inMatrix.GetElement(inMatrix, 1).z) - (inMatrix.GetElement(inMatrix, 0).z * inMatrix.GetElement(inMatrix, 1).x);
	matrix[8] = (inMatrix.GetElement(inMatrix, 0).x * inMatrix.GetElement(inMatrix, 1).y) - (inMatrix.GetElement(inMatrix, 0).y * inMatrix.GetElement(inMatrix, 1).x);

	double determinant = 1 / ((inMatrix.GetElement(inMatrix, 0).x * matrix[0]) - (inMatrix.GetElement(inMatrix, 0).y * matrix[1]) + (inMatrix.GetElement(inMatrix, 0).z * matrix[2]));

	matrix[3] = -matrix[1];
	matrix[6] = matrix[2];
	matrix[1] = -matrix[3];
	matrix[7] = -matrix[5];
	matrix[2] = matrix[6];
	matrix[5] = -matrix[7];

	Matrix33d adjugate(matrix);

	return adjugate * determinant;
}