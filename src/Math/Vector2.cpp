/*
* @author PELLETIER Benoit
*
* @file Vector2.cpp
*
* @date 13/03/2019
*
* @brief Class for 2D vector manipulation
*
*/

#include "stdafx.h"
#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(float _x, float _y)
	: x(_x), y(_y)
{
}

float Vector2::length() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::lengthSq() const
{
	return x * x + y * y;
}

void Vector2::normalize()
{
	float l = length();
	x /= l;
	y /= l;
}

Vector2 Vector2::normalized() const
{
	float l = length();
	return Vector2(x / l, y / l);
}

void Vector2::clamp(float _min, float _max)
{
	float ll = lengthSq();
	if (ll < _min*_min)
	{
		normalize();
		x *= _min;
		y *= _min;
	}
	else if (ll > _max*_max)
	{
		normalize();
		x *= _max;
		y *= _max;
	}
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 & Vector2::operator+=(const Vector2 & _v)
{
	x += _v.x;
	y += _v.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & _v)
{
	x -= _v.x;
	y -= _v.y;
	return *this;
}

Vector2 & Vector2::operator*=(float _f)
{
	x *= _f;
	y *= _f;
	return *this;
}

Vector2 & Vector2::operator/=(float _f)
{
	x /= _f;
	y /= _f;
	return *this;
}

float Vector2::Dot(const Vector2 & _a, const Vector2 & _b)
{
	return _a.x * _b.x + _a.y * _b.y;
}

float Vector2::Dist(const Vector2 & _a, const Vector2 & _b)
{
	return (_a - _b).length();
}

float Vector2::DistSq(const Vector2 & _a, const Vector2 & _b)
{
	return (_a - _b).lengthSq();
}

Vector2 Vector2::Clamp(const Vector2 & _v, float _min, float _max)
{
	Vector2 v(_v);
	v.clamp(_min, _max);
	return v;
}


bool operator==(const Vector2& _a, const Vector2& _b)
{
	return _a.x == _b.x && _a.y == _b.y;
}

bool operator!=(const Vector2& _a, const Vector2& _b)
{
	return _a.x != _b.x || _a.y != _b.y;
}

Vector2 operator+(const Vector2& _a, const Vector2& _b)
{
	return Vector2(_a.x + _b.x, _a.y + _b.y);
}

Vector2 operator-(const Vector2& _a, const Vector2& _b)
{
	return Vector2(_a.x - _b.x, _a.y - _b.y);
}

Vector2 operator*(float _a, const Vector2& _b)
{
	return Vector2(_b.x * _a, _b.y * _a);
}

Vector2 operator*(const Vector2& _a, float _b)
{
	return Vector2(_a.x * _b, _a.y * _b);
}

Vector2 operator/(const Vector2& _a, float _b)
{
	return Vector2(_a.x / _b, _a.y / _b);
}

