/*
* @author PELLETIER Benoit
*
* @file Button.cpp
*
* @date 03/10/2018
*
* @brief Button class with SFML
*
*/

#include "Button.h"
#include <cassert>


Button::Button(int x, int y, int width, int height, UIStyle& style)
	: AbstractUI(x, y, width, height, style)
	, m_string("")
	, m_maxLength(0)
{
	m_text = new sf::Text();
	assert(nullptr != m_text);
}

Button::Button(const Button & _b)
	: AbstractUI(_b)
	, m_string(_b.m_string)
	, m_maxLength(_b.m_maxLength)
{
	m_text = new sf::Text(*_b.m_text);
	assert(nullptr != m_text);
}

Button::Button(Button && _b)
	: AbstractUI(_b)
{
	_b.swap(*this);
}

Button::~Button()
{
	if (nullptr != m_text)
	{
		delete m_text;
	}
}

Button & Button::operator=(Button && _b)
{
	_b.swap(*this);
	return *this;
}

void Button::swap(Button & _other)
{
	AbstractUI::swap(_other);
	std::swap(m_text, _other.m_text);
	std::swap(m_string, _other.m_string);
	std::swap(m_maxLength, _other.m_maxLength);
}

//void Button::SetNormalTexture(int x, int y, int w, int h)
//{
//	m_normalRect = sf::IntRect(x, y, w, h);
//}
//
//void Button::SetClickedTexture(int x, int y, int w, int h)
//{
//	m_clickedRect = sf::IntRect(x, y, w, h);
//}

void Button::setText(std::string text)
{
	m_string = text;
	updateDisplayedText();
}

std::string Button::getText() const
{
	return m_string;
}

void Button::setMaxTextLength(size_t maxLength)
{
	m_maxLength = maxLength;
	updateDisplayedText();
}

size_t Button::getMaxTextLength() const
{
	return m_maxLength;
}

//void Button::update()
//{
//	AbstractUI::update();
//
//	/*sf::FloatRect textRect = m_text->getLocalBounds();
//	float posX = m_rect->getPosition().x + (int)(m_rect->getSize().x) / 2 - (int)(textRect.width + textRect.left) / 2;
//	float posY = m_rect->getPosition().y + (int)(m_rect->getSize().y) / 2 - m_text->getCharacterSize() * 0.6f;
//	m_text->setPosition(posX, posY);
//
//	m_text->setColor((*m_style)[m_state].fgCol);*/
//}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);
	target.draw(*m_text);
}

void Button::_updateTransform()
{
	AbstractUI::_updateTransform();
	sf::FloatRect textRect = m_text->getLocalBounds();
	float posX = m_rect->getPosition().x + (int)(m_rect->getSize().x) / 2 - (int)(textRect.width + textRect.left) / 2;
	float posY = m_rect->getPosition().y + (int)(m_rect->getSize().y) / 2 - m_text->getCharacterSize() * 0.6f;
	m_text->setPosition((int)posX, (int)posY);
}

void Button::_updateStyle()
{
	AbstractUI::_updateStyle();
	m_text->setFillColor((*m_style)[m_state].fgCol);
	m_text->setFont(*m_style->getFont());
	m_text->setCharacterSize(m_style->getCharacterSize());
}

void Button::updateDisplayedText()
{
	if (nullptr != m_text)
	{
		if (m_maxLength > 0 && m_string.size() > m_maxLength)
		{
			m_text->setString(m_string.substr(0, m_maxLength - 3) + "...");
		}
		else
		{
			m_text->setString(m_string);
		}
	}
}