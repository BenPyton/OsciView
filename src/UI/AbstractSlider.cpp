/*
* @author PELLETIER Benoit
*
* @file AbstractSlider.cpp
*
* @date 13/09/2020
*
* @brief Define an abstract class for all slider type UI (eg. Slider, Dial, AbstractSlider)
*
*/

#include "AbstractSlider.h"

AbstractSlider::AbstractSlider(int x, int y, int w, int h, UIStyle& style)
	: AbstractUI(x, y, w, h, style)
{
	m_minValue = 0;
	m_maxValue = 100;
	m_value = 0;
}

AbstractSlider::~AbstractSlider()
{
}

void AbstractSlider::_updateState()
{
	AbstractUI::_updateState();
	m_valueChanged = false;
}
