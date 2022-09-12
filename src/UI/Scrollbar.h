/*
* @author PELLETIER Benoit
*
* @file Scrollbar.h
*
* @date 23/02/2019
*
* @brief Define a scroll bar UI
*
*/

#ifndef _SCROLLBAR_H
#define _SCROLLBAR_H

#include <iostream>
#include "AbstractSlider.h"

using namespace std;

class Scrollbar : public AbstractSlider
{
public:
	Scrollbar(int x, int y, int w, int h, UIStyle& style = UIStyle::Default);
	virtual ~Scrollbar();

	int getViewedStep() { return m_viewedStep; }
	void setViewedStep(int _viewedStep) { m_viewedStep = _viewedStep; }

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	virtual void _updateState() override;
	virtual void _updateTransform() override;
	virtual void _updateStyle() override;

private:
	sf::RectangleShape* m_handle;
	sf::Vector2f m_mouseOffset;
	int m_startValue;
	int m_viewedStep;
	bool m_dragging;
};

#endif // _SCROLLBAR_H