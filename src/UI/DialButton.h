/*
* @author PELLETIER Benoit
*
* @file DialButton.h
*
* @date 13/09/2020
*
* @brief Define a dial button UI
*
*/

#ifndef DIALBUTTON_H
#define DIALBUTTON_H

#include <iostream>
#include "AbstractSlider.h"

using namespace std;

class DialButton : public AbstractSlider
{
public:
	enum class LabelPosition {
		TOP,
		BOTTOM,
	};

	DialButton(int x, int y, int w, int h, UIStyle& style = UIStyle::Default);
	virtual ~DialButton();

	void setLabel(std::string _label);
	std::string getLabel() const;
	void setMinAngle(float _minAngle);
	float getMinAngle() const;
	void setMaxAngle(float _maxAngle);
	float getMaxAngle() const;
	inline void setLoopable(bool _loopable) { m_loopable = _loopable; }
	inline bool getLoopable() const { return m_loopable; }
	inline void setLabelPosition(LabelPosition _position) { m_labelPosition = _position; }
	inline LabelPosition getLabelPosition() const { return m_labelPosition; }

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	virtual void _updateState() override;
	virtual void _updateTransform() override;
	virtual void _updateStyle() override;

private:
	sf::CircleShape* m_button;
	sf::RectangleShape* m_cursor;
	sf::Vector2f m_mouseOffset;
	bool m_dragging;
	int m_startValue;
	sf::Text* m_label;
	sf::Text* m_value;
	float m_minAngle;
	float m_maxAngle;
	bool m_loopable;
	LabelPosition m_labelPosition;
};

#endif // DIALBUTTON_H