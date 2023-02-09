/*
* @author PELLETIER Benoit
*
* @file AbstractUI.h
*
* @date 06/10/2018
*
* @brief Define a base class for UI elements
*
*/

#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Core/Input.h"
#include "UIStyle.h"

using namespace std;

class View;

class AbstractUI : public sf::Drawable
{
public:
	enum class Stretch { NONE = 0, HORIZONTAL = 1, VERTICAL = 2 };

	AbstractUI(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	AbstractUI(const AbstractUI& _aui);
	AbstractUI(AbstractUI&& _aui);
	virtual ~AbstractUI();
	AbstractUI& operator=(const AbstractUI& _aui) = delete;
	AbstractUI& operator=(AbstractUI&& _aui);
	void swap(AbstractUI& _other);

	// Accessors
	void setAnchor(sf::Vector2f anchor);

	void setAnchorMin(sf::Vector2f anchorMin);
	sf::Vector2f getAnchorMin() const;

	void setAnchorMax(sf::Vector2f anchorMax);
	sf::Vector2f getAnchorMax() const;

	void setPivot(sf::Vector2f pivot);
	sf::Vector2f getPivot() const;

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;

	void setStretch(Stretch _stretch);
	Stretch getStretch() const;

	void setSize(sf::Vector2f size);
	sf::Vector2f getSize() const;

	sf::Vector2f getRealPosition();
	sf::Vector2f getRealSize() const;

	void setEnabled(bool enabled);
	bool getEnabled() const;

	void setFocused(bool focused);
	bool getFocused() const;

	void setParent(AbstractUI* parent) { m_parent = parent; }
	AbstractUI* getParent() const { return m_parent; }

	void setViewParent(View* parent) { m_viewParent = parent; }
	View* getViewParent() const { return m_viewParent; }

	void setStyle(UIStyle* style) { m_style = style; }
	UIStyle* getStyle() const { return m_style; }

	void setMargins(float left, float right, float top, float bottom);
	void getMargins(float& left, float& right, float& top, float& bottom) const;

	bool hovered(sf::Vector2f pos);
	bool click();
	virtual void update();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
	virtual void _updateState();
	virtual void _updateTransform();
	virtual void _updateStyle();

protected:
	AbstractUI* m_parent;
	View* m_viewParent;

	bool m_enabled;
	bool m_focused;
	sf::RectangleShape* m_rect;

	UIState m_state;
	UIStyle* m_style;

	sf::Vector2f m_anchorMin, m_anchorMax;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_pivot;
	float m_marginTop, m_marginLeft, m_marginBottom, m_marginRight;

	Stretch m_stretch;
};

#endif // ABSTRACTUI_H