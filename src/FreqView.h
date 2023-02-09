#ifndef FREQVIEW_H
#define FREQVIEW_H

#include "UI/AbstractUI.h"
#include <vector>

class FreqView : public AbstractUI
{
public:
	FreqView(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	FreqView(const FreqView& _fv);
	FreqView(FreqView&& _fv);
	virtual ~FreqView();
	FreqView& operator=(const FreqView& _fv) = delete;
	FreqView& operator=(FreqView&& _fv);
	void swap(FreqView& _other);

	void setSamples(std::vector<double>* _samples);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void _updateState() override;

private:
	std::vector<double>* m_samples = nullptr;
	sf::VertexArray* m_vertices = nullptr;
	sf::Color m_color;
};

#endif // FREQVIEW_H
