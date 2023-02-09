/*
* @author PELLETIER Benoit
*
* @file Button.h
*
* @date 03/10/2018
*
* @brief Button class with SFML
*
*/

#ifndef BUTTON_H
#define BUTTON_H


#include <SFML/Graphics.hpp>
#include "AbstractUI.h"

class Button : public AbstractUI
{
protected:
	sf::Text* m_text;
	std::string m_string;
	size_t m_maxLength;

public:
	// Constructor
	Button(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	Button(const Button& _b);
	Button(Button&& _b);
	virtual ~Button();
	Button& operator=(const Button&) = delete;
	Button& operator=(Button&& _b);
	void swap(Button& _other);

	// Accessors
	void setText(std::string text);
	string getText() const;
	void setMaxTextLength(size_t maxLength);
	size_t getMaxTextLength() const;
	/*void SetNormalTexture(int x, int y, int w, int h);
	void SetClickedTexture(int x, int y, int w, int h);*/
	//virtual void update() override;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	//virtual void _updateState() override;
	virtual void _updateTransform() override;
	virtual void _updateStyle() override;

	void updateDisplayedText();
};


#endif // BUTTON_H