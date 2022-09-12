/*
* @author PELLETIER Benoit
*
* @file Utils.cpp
*
* @date 04/10/2018
*
* @brief Some utility functions
*
*/

#include "Utils.h"
#include "Window.h"
#include <math.h>

string readFile(string filename)
{
	string text = "";
	int length;
	char buffer[MAX_BUFFER_SIZE] = { 0 };

	ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		file.seekg(0, ios_base::end);
		length = (int)file.tellg();
		file.seekg(0, ios_base::beg);
		if (length > MAX_BUFFER_SIZE)
		{
			length = MAX_BUFFER_SIZE;
		}

		file.read(buffer, length);

		file.close();

		text = buffer;
	}
	else
	{
		printf("Error when loading file %s\n", filename.c_str());
	}


	return text;
}

string floatToStr(float number, int precision)
{
	stringstream ss;
	ss << fixed << setprecision(precision) << number;
	return ss.str();
}

string intToStr(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}

void drawPixel(sf::Vector2f pixel, sf::Color color)
{
	sf::Vertex v(pixel, color);
	Window::Draw(&v, 1, sf::PrimitiveType::Points);
}

void drawLine(sf::Vector2f p1, sf::Vector2f p2, sf::Color color)
{
	sf::Vertex v[2] = { sf::Vertex(p1, color), sf::Vertex(p2, color) };
	Window::Draw(v, 2, sf::PrimitiveType::Lines);
}

float mapValue(float x, float p00, float p01, float p10, float p11)
{
	float newValue = 0.0f;
	if (p00 != p01 && p10 != p11)
	{
		float a = x - p00;
		//float b ? ;
		float max0 = p01 - p00;
		float max1 = p11 - p10;
		newValue = p10 + a * (max1 / max0);
	}

	return newValue;
}

float mod(float x, float min, float max)
{
	float step = max - min;
	while(x < min)
		x += step;
	while(x > max)
		x -= step;
	return x;
}

int mod(int x, int min, int max)
{
	int step = max - min;
	while(x < min)
		x += step;
	while(x > max)
		x -= step;
	return x;
}

float clamp(float x, float min, float max)
{
	if (x < min) x = min;
	if (x > max) x = max;
	return x;
}

int clamp(int x, int min, int max)
{
	if(x < min) x = min;
	if(x > max) x = max;
	return x;
}

float length(float x, float y)
{
	return sqrt(x * x + y * y);
}

float lengthSq(float x, float y)
{
	return x * x + y * y;
}

float length(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float lengthSq(sf::Vector2f v)
{
	return v.x * v.x + v.y * v.y;
}

void DFT(const vector<double>& in, vector<double>& out)
{
	size_t n = in.size();
	size_t outN = n / 2;
	out.resize(n / 2);
	for(size_t k = 0; k < outN; ++k) // For each output element
	{
		double sumreal = 0;
		double sumimag = 0;
		for(size_t t = 0; t < n; ++t)  // For each input element
		{
			double angle = 2 * _PI * t * k / n;
			sumreal += in[t] * std::cos(angle);
			sumimag += -in[t] * std::sin(angle);
		}
		out[k] = std::sqrt(sumreal * sumreal + sumimag * sumimag);
	}
}

sf::Color fromHSV(float h, float s, float v)
{
	float C = s * v;
	float X = C * (1.0f - abs(mod(h * 6.f, 0.0f, 2.0f) - 1.0f));
	float m = v - C;

	float step = 1. / 6.;
	float r = 0.0f, g = 0.0f, b = 0.0f;
	if(h >= 0.f && h < step)
	{
		r = C;
		g = X;
	}
	if(h >= step && h < 2.f * step)
	{
		r = X;
		g = C;
	}
	if(h >= 2.f * step && h < 3.f * step)
	{
		g = C;
		b = X;
	}
	if(h >= 3.f * step && h < 4.f * step)
	{
		g = X;
		b = C;
	}
	if(h >= 4.f * step && h < 6.f * step)
	{
		r = X;
		b = C;
	}
	if(h >= 5.f*step && h < 1.f)
	{
		r = C;
		b = X;
	}

	return sf::Color(round((r + m) * UINT8_MAX), round((g + m) * UINT8_MAX), round((b + m) * UINT8_MAX));
}


sf::Color lerp(const sf::Color& a, const sf::Color& b, float t)
{
	return sf::Color(
		a.r * t + b.r * (1 - t),
		a.g * t + b.g * (1 - t),
		a.b * t + b.b * (1 - t),
		a.a * t + b.a * (1 - t)
	);
}
