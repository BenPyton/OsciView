/*
* @author PELLETIER Benoit
*
* @file Matrix3.h
*
* @date 13/03/2019
*
* @brief Class to manipulate 3x3 Matrices
*
*/

#ifndef _MATRIX3_H
#define _MATRIX3_H

#include <iostream>
#include "Vector3.h"

using namespace std;

class Matrix3
{
private:
	float m_values[9];

public:
	Matrix3();
	Matrix3(
		float _m00, float _m01, float _m02, 
		float _m10, float _m11, float _m12,
		float _m20, float _m21, float _m22);

	// Change this matrix to it's inverse
	void inverse();

	// Return inverse of this matrix (but don't change this matrix)
	Matrix3 inversed() const;

	// Change this matrix to it's transform
	void transpose();

	// Return transpose of this matrix (but don't change this matrix)
	Matrix3 transposed() const;

	float det() const;

	// Unary operators
	Matrix3 operator-();

	// Compound operators
	Matrix3& operator+=(const Matrix3& _m);
	Matrix3& operator-=(const Matrix3& _m);
	Matrix3& operator*=(const Matrix3& _m);
	Matrix3& operator*=(float _f);
	Matrix3& operator/=(float _f);

	// Accessor operators
	float operator()(int _i, int _j) const;
	float& operator()(int _i, int _j);
	float operator[](int _i) const;
	float& operator[](int _i);
};

// Comparison operators
bool operator==(const Matrix3& _a, const Matrix3& _b);
bool operator!=(const Matrix3& _a, const Matrix3& _b);

// Binary operators
Matrix3 operator+(const Matrix3& _a, const Matrix3& _b);
Matrix3 operator-(const Matrix3& _a, const Matrix3& _b);
Matrix3 operator*(const Matrix3& _a, const Matrix3& _b);
Vector3 operator*(const Matrix3& _m, Vector3& _v);
Matrix3 operator*(float _f, const Matrix3& _m);
Matrix3 operator*(const Matrix3& _m, float _f);
Matrix3 operator/(const Matrix3& _m, float _f);

#endif // _MATRIX3_H