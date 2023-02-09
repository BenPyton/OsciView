/*
* @author PELLETIER Benoit
*
* @file Vector2.h
*
* @date 13/03/2019
*
* @brief Class for 2D vector manipulation
*
*/

#ifndef VECTOR2_H
#define VECTOR2_H

#include <SFML/System.hpp>
#include <iostream>

using namespace std;

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float _x, float _y);

	float length() const;
	float lengthSq() const;

	// Change this vector to it's normalized version
	void normalize();

	// Return a new normailzed vector without changing this vector
	Vector2 normalized() const;

	// Change this vector by clamping the length of the vector
	void clamp(float _min, float _max);

	// Unary operators
	Vector2 operator-();

	// Compounds operators
	Vector2& operator+=(const Vector2& _v);
	Vector2& operator-=(const Vector2& _v);
	Vector2& operator*=(float _f);
	Vector2& operator/=(float _f);

	// Conversions into sfml 2D vector
	inline operator sf::Vector2f() const { return sf::Vector2f(x, y); };
	//explicit inline operator sf::Vector2f() const { return sf::Vector2f(x, y); };

	static float Dot(const Vector2& _a, const Vector2& _b);
	static float Dist(const Vector2& _a, const Vector2& _b);
	static float DistSq(const Vector2& _a, const Vector2& _b);
	static Vector2 Clamp(const Vector2& _v, float _min, float _max);
};

// Comparison operators
bool operator==(const Vector2& _a, const Vector2& _b);
bool operator!=(const Vector2& _a, const Vector2& _b);

// Binary operators
Vector2 operator+(const Vector2& _a, const Vector2& _b);
Vector2 operator-(const Vector2& _a, const Vector2& _b);
Vector2 operator*(float _a, const Vector2& _b);
Vector2 operator*(const Vector2& _a, float _b);
Vector2 operator/(const Vector2& _a, float _b);


#endif // VECTOR2_H