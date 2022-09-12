/*
* @author PELLETIER Benoit
*
* @file Scrollbar.cpp
*
* @date 23/02/2019
*
* @brief Define a scroll bar UI
*
*/

#include "Scrollbar.h"
#include "../Core/Utils.h"

Scrollbar::Scrollbar(int x, int y, int w, int h, UIStyle& style)
	: AbstractSlider(x, y, w, h, style), m_mouseOffset()
{
	m_handle = new sf::RectangleShape();
	m_dragging = false;
	m_viewedStep = 10;
	m_startValue = 0;
}

Scrollbar::~Scrollbar()
{
	delete m_handle;
}

void Scrollbar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	AbstractSlider::draw(target, states);
	target.draw(*m_handle, states);
}

void Scrollbar::_updateState()
{
	if (m_dragging)
	{
		sf::Vector2f deltaPos = Input::GetMousePosition() - m_mouseOffset;

		int nbStep = getMaximum() - getMinimum() + getViewedStep();
		setValue(m_startValue + (deltaPos.x / getRealSize().x) * nbStep);

		if (Input::GetMouseButtonUp(sf::Mouse::Left))
		{
			m_dragging = false;
			m_state = UIState::UI_NORMAL;
		}
	}
	else if (m_handle->getGlobalBounds().contains(Input::GetMousePosition()))
	{
		m_state = UIState::UI_HOVERED;
		if (Input::GetMouseButtonDown(sf::Mouse::Left))
		{
			m_state = UIState::UI_CLICKED;
			m_dragging = true;
			m_mouseOffset = Input::GetMousePosition();
			m_startValue = getValue();
		}
	}
	else
	{
		m_state = UIState::UI_NORMAL;
	}
}

void Scrollbar::_updateTransform()
{
	AbstractSlider::_updateTransform();

	int nbStep = getMaximum() - getMinimum() + getViewedStep();
	float handleSize = (getViewedStep() / static_cast<float>(nbStep)) * getRealSize().x;
	float handlePos = ((getValue() - getMinimum()) / static_cast<float>(nbStep)) * getRealSize().x;

	m_handle->setPosition(sf::Vector2f(handlePos, 0) + getRealPosition());
	m_handle->setSize(sf::Vector2f(handleSize, getRealSize().y));
}

void Scrollbar::_updateStyle()
{
	AbstractSlider::_updateStyle();

	m_rect->setFillColor((*m_style)[UIState::UI_NORMAL].bgCol);
	m_rect->setOutlineColor((*m_style)[UIState::UI_NORMAL].outCol);
	m_rect->setOutlineThickness((*m_style)[UIState::UI_NORMAL].outThick);

	m_handle->setFillColor((*m_style)[m_state].bgCol);
	m_handle->setOutlineColor((*m_style)[m_state].outCol);
	m_handle->setOutlineThickness((*m_style)[m_state].outThick);
}
