/*
* @author PELLETIER Benoit
*
* @file AbstractSlider.h
*
* @date 13/09/2020
*
* @brief Define an abstract class for all slider type UI (eg. Slider, Dial, AbstractSlider)
*
*/

#ifndef _ABSTRACTSLIDER_H
#define _ABSTRACTSLIDER_H

#include <iostream>
#include "AbstractUI.h"
#include "../Core/Utils.h"

using namespace std;

class AbstractSlider : public AbstractUI
{
public:
	AbstractSlider(int x, int y, int w, int h, UIStyle& style = UIStyle::Default);
	virtual ~AbstractSlider();

	int getValue() { return m_value; }
	void setValue(int _value) { m_value = clamp(_value, m_minValue, m_maxValue); m_valueChanged = true; }

	int getMinimum() { return m_minValue; }
	void setMinimum(int _minimum) { m_minValue = _minimum; setValue(m_value); }

	int getMaximum() { return m_maxValue; }
	void setMaximum(int _maximum) { m_maxValue = _maximum; setValue(m_value); }

	bool valueChanged() { return m_valueChanged; }

protected:
	virtual void _updateState() override;

private:
	int m_minValue;
	int m_maxValue;
	int m_value;
	bool m_valueChanged;
};

#endif // _ABSTRACTSLIDER_H