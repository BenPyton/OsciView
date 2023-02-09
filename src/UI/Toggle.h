/*
* @author PELLETIER Benoit
*
* @file Toggle.h
*
* @date 07/10/2018
*
* @brief Define a toggle (checkbox) in SFML
*
*/

#ifndef TOGGLE_H
#define TOGGLE_H

#include <iostream>
#include "Button.h"

using namespace std;

class Toggle : public Button
{
private:

	bool m_checked;

public:
	Toggle(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	~Toggle();

	void setChecked(bool checked);
	bool getChecked() const;
	//virtual void update() override;

protected:
	virtual void _updateState() override;
	/*virtual void _updateTransform() override;
	virtual void _updateStyle() override;*/
};

#endif // TOGGLE_H