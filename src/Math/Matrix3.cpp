/*
* @author PELLETIER Benoit
*
* @file Matrix3.cpp
*
* @date 13/03/2019
*
* @brief Class to manipulate 3x3 Matrices
*
*/

#include "Matrix3.h"

#define _00 0
#define _01 1
#define _02 2
#define _10 3
#define _11 4
#define _12 5
#define _20 6
#define _21 7
#define _22 8

Matrix3::Matrix3()
	: m_values { 0 }
{
}

Matrix3::Matrix3(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12, float _m20, float _m21, float _m22)
	: m_values { _m00, _m01, _m02, _m10, _m11, _m12, _m20, _m21, _m22 }
{
}

void Matrix3::inverse()
{
	*this = inversed();
}

Matrix3 Matrix3::inversed() const
{
	float d = det();
	if (d != 0)
	{
		Matrix3 m( // transposed comatrix
			m_values[_11] * m_values[_22] - m_values[_12] * m_values[_21],
			m_values[_02] * m_values[_21] - m_values[_01] * m_values[_22],
			m_values[_01] * m_values[_12] - m_values[_11] * m_values[_02],

			m_values[_12] * m_values[_20] - m_values[_10] * m_values[_22],
			m_values[_00] * m_values[_22] - m_values[_02] * m_values[_20],
			m_values[_02] * m_values[_10] - m_values[_00] * m_values[_12],

			m_values[_10] * m_values[_21] - m_values[_11] * m_values[_20],
			m_values[_01] * m_values[_20] - m_values[_00] * m_values[_21],
			m_values[_11] * m_values[_00] - m_values[_01] * m_values[_10]
		);

		m *= 1.0f / d;
		return m;
	}
	return Matrix3();
}

void Matrix3::transpose()
{
	*this = transposed();
}

Matrix3 Matrix3::transposed() const
{
	return Matrix3(
		m_values[_00], m_values[_10], m_values[_20],
		m_values[_01], m_values[_11], m_values[_21],
		m_values[_02], m_values[_12], m_values[_22]);
}

float Matrix3::det() const
{
	return 
		  m_values[_00] * (m_values[_11] * m_values[_22] - m_values[_12] * m_values[_21])
		- m_values[_01] * (m_values[_10] * m_values[_22] - m_values[_12] * m_values[_20])
		+ m_values[_02] * (m_values[_10] * m_values[_21] - m_values[_11] * m_values[_20]);
}

Matrix3 Matrix3::operator-()
{
	return Matrix3(
		-m_values[0], -m_values[1], -m_values[2],
		-m_values[3], -m_values[4], -m_values[5],
		-m_values[6], -m_values[7], -m_values[8]);
}

Matrix3 & Matrix3::operator+=(const Matrix3 & _m)
{
	for (int i = 0; i < 9; i++)
	{
		m_values[i] += _m.m_values[i];
	}
	return *this;
}

Matrix3 & Matrix3::operator-=(const Matrix3 & _m)
{
	for (int i = 0; i < 9; i++)
	{
		m_values[i] -= _m.m_values[i];
	}
	return *this;
}

Matrix3 & Matrix3::operator*=(const Matrix3 & _m)
{
	Matrix3 m(*this * _m);
	*this = m;
	return *this;
}

Matrix3 & Matrix3::operator*=(float _f)
{
	for (int i = 0; i < 9; i++)
	{
		m_values[i] *= _f;
	}
	return *this;
}

Matrix3 & Matrix3::operator/=(float _f)
{
	for (int i = 0; i < 9; i++)
	{
		m_values[i] /= _f;
	}
	return *this;
}

float Matrix3::operator()(int _i, int _j) const
{
	if(_i >= 0 && _i < 3 && _j >= 0 && _j < 3)
		return m_values[_i * 3 + _j];
	return 0;
}

float & Matrix3::operator()(int _i, int _j)
{
	return m_values[_i * 3 + _j];
}

float Matrix3::operator[](int _i) const
{
	return m_values[_i];
}

float & Matrix3::operator[](int _i)
{
	return m_values[_i];
}

bool operator==(const Matrix3 & _a, const Matrix3 & _b)
{
	return _a(0, 0) == _b(0, 0) && _a(0, 1) == _b(0, 1) && _a(0, 2) == _b(0, 2)
		&& _a(1, 0) == _b(1, 0) && _a(1, 1) == _b(1, 1) && _a(1, 2) == _b(1, 2)
		&& _a(2, 0) == _b(2, 0) && _a(2, 1) == _b(2, 1) && _a(2, 2) == _b(2, 2);
}

bool operator!=(const Matrix3 & _a, const Matrix3 & _b)
{
	return _a(0, 0) != _b(0, 0) || _a(0, 1) != _b(0, 1) || _a(0, 2) != _b(0, 2)
		|| _a(1, 0) != _b(1, 0) || _a(1, 1) != _b(1, 1) || _a(1, 2) != _b(1, 2)
		|| _a(2, 0) != _b(2, 0) || _a(2, 1) != _b(2, 1) || _a(2, 2) != _b(2, 2);
}

Matrix3 operator+(const Matrix3 & _a, const Matrix3 & _b)
{
	return Matrix3(
		_a(0, 0) + _b(0, 0), _a(0, 1) + _b(0, 1), _a(0, 2) + _b(0, 2),
		_a(1, 0) + _b(1, 0), _a(1, 1) + _b(1, 1), _a(1, 2) + _b(1, 2), 
		_a(2, 0) + _b(2, 0), _a(2, 1) + _b(2, 1), _a(2, 2) + _b(2, 2));
}

Matrix3 operator-(const Matrix3 & _a, const Matrix3 & _b)
{
	return Matrix3(
		_a(0, 0) - _b(0, 0), _a(0, 1) - _b(0, 1), _a(0, 2) - _b(0, 2),
		_a(1, 0) - _b(1, 0), _a(1, 1) - _b(1, 1), _a(1, 2) - _b(1, 2),
		_a(2, 0) - _b(2, 0), _a(2, 1) - _b(2, 1), _a(2, 2) - _b(2, 2));
}

Matrix3 operator*(const Matrix3 & _a, const Matrix3 & _b)
{
	return Matrix3(
		_a(0, 0) * _b(0, 0) + _a(0, 1) * _b(1, 0) + _a(0, 2) * _b(2, 0),
		_a(0, 0) * _b(0, 1) + _a(0, 1) * _b(1, 1) + _a(0, 2) * _b(2, 1),
		_a(0, 0) * _b(0, 2) + _a(0, 1) * _b(1, 2) + _a(0, 2) * _b(2, 2),

		_a(1, 0) * _b(0, 0) + _a(1, 1) * _b(1, 0) + _a(1, 2) * _b(2, 0),
		_a(1, 0) * _b(0, 1) + _a(1, 1) * _b(1, 1) + _a(1, 2) * _b(2, 1),
		_a(1, 0) * _b(0, 2) + _a(1, 1) * _b(1, 2) + _a(1, 2) * _b(2, 2),

		_a(2, 0) * _b(0, 0) + _a(2, 1) * _b(1, 0) + _a(2, 2) * _b(2, 0),
		_a(2, 0) * _b(0, 1) + _a(2, 1) * _b(1, 1) + _a(2, 2) * _b(2, 1),
		_a(2, 0) * _b(0, 2) + _a(2, 1) * _b(1, 2) + _a(2, 2) * _b(2, 2));
}

Vector3 operator*(const Matrix3 & _m, Vector3 & _v)
{
	return Vector3(
		_m(0, 0) * _v.x + _m(0, 1) * _v.y + _m(0, 2) * _v.z,
		_m(1, 0) * _v.x + _m(1, 1) * _v.y + _m(1, 2) * _v.z,
		_m(2, 0) * _v.x + _m(2, 1) * _v.y + _m(2, 2) * _v.z);
}

Matrix3 operator*(float _f, const Matrix3 & _m)
{
	return Matrix3(
		_m(0, 0) * _f, _m(0, 1) * _f, _m(0, 2) * _f,
		_m(1, 0) * _f, _m(1, 1) * _f, _m(1, 2) * _f,
		_m(2, 0) * _f, _m(2, 1) * _f, _m(2, 2) * _f);
}

Matrix3 operator*(const Matrix3 & _m, float _f)
{
	return Matrix3(
		_m(0, 0) * _f, _m(0, 1) * _f, _m(0, 2) * _f,
		_m(1, 0) * _f, _m(1, 1) * _f, _m(1, 2) * _f,
		_m(2, 0) * _f, _m(2, 1) * _f, _m(2, 2) * _f);
}

Matrix3 operator/(const Matrix3 & _m, float _f)
{
	return Matrix3(
		_m(0, 0) / _f, _m(0, 1) / _f, _m(0, 2) / _f,
		_m(1, 0) / _f, _m(1, 1) / _f, _m(1, 2) / _f,
		_m(2, 0) / _f, _m(2, 1) / _f, _m(2, 2) / _f);
}
