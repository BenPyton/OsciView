/*
* @author PELLETIER Benoit
*
* @file Time.h
*
* @date 03/10/2018
*
* @brief Manage frame time in SFML
*
*/

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <assert.h>
#include <SFML/System.hpp>

#define BUFFER_SIZE 30

using namespace std;

class Time
{
private:
	static Time m_instance;

	sf::Clock m_clock;
	float m_deltaTime;
	float m_deltaBuffer[BUFFER_SIZE];
	int m_bufferIndex;
	float m_bufferAverage;

	Time();
	void _LockFramerate(int framerate);
public:
	~Time();


	static float GetDeltaTime();
	static float GetFps();
	static void LockFramerate(int framerate);
};

#endif // TIME_H
