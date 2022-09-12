/*
* @author PELLETIER Benoit
*
* @file Vector3.cpp
*
* @date 13/03/2019
*
* @brief Class to manipulate 3D vector
*
*/

#include "stdafx.h"
#include "Vector3.h"
#include <cmath>

Vector3::Vector3()
	: x(0), y(0), z(0)
{
}

Vector3::Vector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

float Vector3::length() const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::lengthSq() const
{
	return x * x + y * y + z * z;
}

void Vector3::normalize()
{
	float l = length();
	x /= l;
	y /= l;
	z /= l;
}

Vector3 Vector3::normalized() const
{
	float l = length();
	return Vector3(x / l, y / l, z / l);
}

void Vector3::clamp(float _min, float _max)
{
	float ll = lengthSq();
	if (ll < _min*_min)
	{
		normalize();
		x *= _min;
		y *= _min;
		z *= _min;
	}
	else if (ll > _max*_max)
	{
		normalize();
		x *= _max;
		y *= _max;
		z *= _max;
	}
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 & Vector3::operator+=(const Vector3 & _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	return *this;
}

Vector3 & Vector3::operator-=(const Vector3 & _v)
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
	return *this;
}

Vector3 & Vector3::operator*=(float _f)
{
	x *= _f;
	y *= _f;
	z *= _f;
	return *this;
}

Vector3 & Vector3::operator/=(float _f)
{
	x /= _f;
	y /= _f;
	z /= _f;
	return *this;
}

float Vector3::Dot(const Vector3 & _a, const Vector3 & _b)
{
	return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

Vector3 Vector3::Cross(const Vector3 & _a, const Vector3 & _b)
{
	return Vector3(_a.y * _b.z - _a.z * _b.y, _a.z * _b.x - _a.x * _b.z, _a.x * _b.y - _a.y * _b.x);
}

float Vector3::Dist(const Vector3 & _a, const Vector3 & _b)
{
	return (_b - _a).length();
}

float Vector3::DistSq(const Vector3 & _a, const Vector3 & _b)
{
	return (_b - _a).lengthSq();
}

Vector3 Vector3::Clamp(const Vector3 & _v, float _min, float _max)
{
	Vector3 v(_v);
	v.clamp(_min, _max);
	return v;
}

bool operator==(const Vector3& _a, const Vector3& _b)
{
	return _a.x == _b.x && _a.y == _b.y && _a.z == _b.z;
}

bool operator!=(const Vector3& _a, const Vector3& _b)
{
	return _a.x != _b.x || _a.y != _b.y || _a.z != _b.z;
}

Vector3 operator+(const Vector3& _a, const Vector3& _b)
{
	return Vector3(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z);
}

Vector3 operator-(const Vector3& _a, const Vector3& _b)
{
	return Vector3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
}

Vector3 operator*(float _a, const Vector3& _b)
{
	return Vector3(_b.x * _a, _b.y * _a, _b.z * _a);
}

Vector3 operator*(const Vector3& _a, float _b)
{
	return Vector3(_a.x * _b, _a.y * _b, _a.z * _b);
}

Vector3 operator/(const Vector3& _a, float _b)
{
	return Vector3(_a.x / _b, _a.y / _b, _a.z / _b);
}

