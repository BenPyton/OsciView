#ifndef SPECTRUMVIEW_H
#define SPECTRUMVIEW_H

#include "UI/AbstractUI.h"
#include <vector>

class SpectrumView : public AbstractUI
{
public:
	SpectrumView(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	SpectrumView(const SpectrumView& _fv);
	SpectrumView(SpectrumView&& _fv);
	virtual ~SpectrumView();
	SpectrumView& operator=(const SpectrumView& _fv) = delete;
	SpectrumView& operator=(SpectrumView&& _fv);
	void swap(SpectrumView& _other);

	void setSamples(std::vector<double>* _samples);

protected:
	virtual void update() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void _updateState() override;

private:
	std::vector<double>* m_samples = nullptr;
	sf::Color m_color;
	sf::Texture* m_tex;
	sf::Sprite* m_spr;
	sf::Image* m_img;
	size_t m_currentIndex;
};

#endif // SPECTRUMVIEW_H
