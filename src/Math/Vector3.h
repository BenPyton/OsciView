/*
* @author PELLETIER Benoit
*
* @file Vector3.h
*
* @date 13/03/2019
*
* @brief Class to manipulate 3D vector
*
*/

#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <iostream>

using namespace std;

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float _x, float _y, float _z);

	float length() const;
	float lengthSq() const;

	// Change this vector to it's normalized version
	void normalize();

	// Return a new normailzed vector without changing this vector
	Vector3 normalized() const;

	// Change this vector by clamping the length of the vector
	void clamp(float _min, float _max);

	// Unary operators
	Vector3 operator-();

	// Compounds operators
	Vector3& operator+=(const Vector3& _v);
	Vector3& operator-=(const Vector3& _v);
	Vector3& operator*=(float _f);
	Vector3& operator/=(float _f);

	static float Dot(const Vector3& _a, const Vector3& _b);
	static Vector3 Cross(const Vector3& _a, const Vector3& _b);
	static float Dist(const Vector3& _a, const Vector3& _b);
	static float DistSq(const Vector3& _a, const Vector3& _b);
	static Vector3 Clamp(const Vector3& _v, float _min, float _max);
};

// Comparison operators
bool operator==(const Vector3& _a, const Vector3& _b);
bool operator!=(const Vector3& _a, const Vector3& _b);

// Binary operators
Vector3 operator+(const Vector3& _a, const Vector3& _b);
Vector3 operator-(const Vector3& _a, const Vector3& _b);
Vector3 operator*(float _a, const Vector3& _b);
Vector3 operator*(const Vector3& _a, float _b);
Vector3 operator/(const Vector3& _a, float _b);

#endif // _VECTOR3_H