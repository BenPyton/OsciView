/*
* @author PELLETIER Benoit
*
* @file DialButton.cpp
*
* @date 13/09/2020
*
* @brief Define a dial button UI
*
*/

#include "DialButton.h"
#include "../Core/Utils.h"

#include <cmath>  // for round

DialButton::DialButton(int x, int y, int w, int h, UIStyle& style)
	: AbstractSlider(x, y, w, h, style)
	, m_mouseOffset()
	, m_dragging(false)
	, m_minAngle(-135.0f)
	, m_maxAngle(135.0f)
	, m_loopable(false)
	, m_labelPosition(LabelPosition::BOTTOM)
{
	m_button = new sf::CircleShape();
	m_cursor = new sf::RectangleShape();
	m_label = new sf::Text();
	m_value = new sf::Text();
}

DialButton::~DialButton()
{
	delete m_button;
	delete m_cursor;
}

void DialButton::setLabel(std::string _label)
{
	m_label->setString(_label);
}

std::string DialButton::getLabel() const
{
	return m_label->getString();
}

void DialButton::setMinAngle(float _minAngle)
{
	m_minAngle = mod(_minAngle, -180.0f, 180.0f);
}

float DialButton::getMinAngle() const
{
	return m_minAngle;
}

void DialButton::setMaxAngle(float _maxAngle)
{
	m_maxAngle = mod(_maxAngle, -180.0f, 180.0f);
}

float DialButton::getMaxAngle() const
{
	return m_maxAngle;
}

void DialButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Dont draw the base rectangle of AbstractUI!

	target.draw(*m_button, states);
	target.draw(*m_cursor, states);
	target.draw(*m_label, states);
	target.draw(*m_value, states);
}

void DialButton::_updateState()
{
	if (m_dragging)
	{
		sf::Vector2f deltaPos = Input::GetMousePosition() - m_mouseOffset;

		float sensibility = 300.0f; // 300px to go from minimum to maximum
		int nbStep = getMaximum() - getMinimum();
		int newValue = m_startValue + round((deltaPos.x / sensibility) * nbStep);
		if(m_loopable)
		{
			newValue = mod(newValue, getMinimum(), getMaximum());
		}
		setValue(newValue);

		if (Input::GetMouseButtonUp(sf::Mouse::Left))
		{
			m_dragging = false;
			m_state = UIState::UI_NORMAL;
		}
	}
	else
	{
		float buttonOffset = (m_labelPosition == DialButton::LabelPosition::TOP) ? 24.0f : 0.0f;

		sf::Vector2f center = getRealPosition() + 0.5f * getRealSize() + sf::Vector2f(0, buttonOffset);;
		float distSq = lengthSq(Input::GetMousePosition() - center);
		float radSq = m_button->getRadius() * m_button->getRadius();
		if(distSq < radSq)
		{
			m_state = UIState::UI_HOVERED;
			if(Input::GetMouseButtonDown(sf::Mouse::Left))
			{
				m_state = UIState::UI_CLICKED;
				m_dragging = true;
				m_startValue = getValue();
				m_mouseOffset = Input::GetMousePosition();
			}
		}
		else
		{
			m_state = UIState::UI_NORMAL;
		}
	}
}

void DialButton::_updateTransform()
{
	AbstractSlider::_updateTransform();

	float radius = min(getRealSize().x, getRealSize().y) * 0.5f;

	float buttonOffset = 0.0f;
	float labelOffset = 0.0f;
	switch (m_labelPosition)
	{
	case DialButton::LabelPosition::TOP:
		buttonOffset = 24.0f;
		labelOffset = -radius - 24.0f - 2;
		break;
	case DialButton::LabelPosition::BOTTOM:
		labelOffset = radius + 2;
		break;
	}

	sf::Vector2f center = getRealPosition() + 0.5f * getRealSize() + sf::Vector2f(0, buttonOffset);
	m_button->setOrigin(sf::Vector2f(radius, radius));
	m_button->setPosition(center);
	m_button->setRadius(radius);

	float cursorAngle = m_minAngle + (m_maxAngle - m_minAngle) * (getValue() - getMinimum()) / static_cast<float>(getMaximum() - getMinimum());
	m_cursor->setRotation(cursorAngle);
	m_cursor->setPosition(center);
	m_cursor->setSize(sf::Vector2f(4, 12));
	m_cursor->setOrigin(sf::Vector2f(2, radius));

	sf::FloatRect valueRect = m_value->getLocalBounds();
	m_value->setPosition(round(center.x - 0.5f * valueRect.width), round(center.y - 0.6f * m_value->getCharacterSize()));
	m_value->setString(intToStr(getValue()));

	sf::FloatRect labelRect = m_label->getLocalBounds();
	m_label->setPosition(round(center.x - 0.5f * labelRect.width), round(center.y + labelOffset));
}

void DialButton::_updateStyle()
{
	AbstractSlider::_updateStyle();

	m_button->setFillColor((*m_style)[m_state].bgCol);
	m_button->setOutlineColor((*m_style)[m_state].outCol);
	m_button->setOutlineThickness((*m_style)[m_state].outThick);

	sf::Color cursorColor = m_state == UIState::UI_CLICKED ? (*m_style)[UIState::UI_NORMAL].bgCol : (*m_style)[UIState::UI_NORMAL].outCol;
	m_cursor->setFillColor(cursorColor);

	m_label->setFont(*(m_style->getFont()));
	m_label->setFillColor((*m_style)[UIState::UI_NORMAL].outCol);
	m_label->setCharacterSize(m_style->getCharacterSize());

	m_value->setFont(*(m_style->getFont()));
	m_value->setFillColor(cursorColor);
	m_value->setCharacterSize(m_style->getCharacterSize());
}
