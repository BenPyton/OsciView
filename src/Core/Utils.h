/*
* @author PELLETIER Benoit
*
* @file Utils.h
*
* @date 04/10/2018
*
* @brief Some utility functions
*
*/

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>


#define MAX_BUFFER_SIZE 1024
#define _PI 3.141592653589
#define _2PI 6.283185307180
#define _SQRT2PI 2.506628274631

using namespace std;

string readFile(string filename);
string floatToStr(float number, int precision);
string intToStr(int number);
void drawPixel(sf::Vector2f pixel, sf::Color color);
void drawLine(sf::Vector2f p1, sf::Vector2f p2, sf::Color color);
float mapValue(float x, float p00, float p01, float p10, float p11);
float mod(float x, float min, float max);
int mod(int x, int min, int max);

float clamp(float x, float min, float max);
int clamp(int x, int min, int max);
float length(float x, float y);
float lengthSq(float x, float y);
float length(sf::Vector2f v);
float lengthSq(sf::Vector2f v);

void DFT(const vector<double>& in, vector<double>& out);

sf::Color fromHSV(float h, float s, float v);
sf::Color lerp(const sf::Color& a, const sf::Color& b, float t);

#endif // UTILS_H