#ifndef FREQVIEW_H
#define FREQVIEW_H

#include "UI/AbstractUI.h"
#include <vector>
#include "Types.h"

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

	void setSamples(const FrequencyBuffer& _samples);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void _updateState() override;

private:
	const FrequencyBuffer* m_samples = nullptr;
	sf::VertexArray* m_vertices = nullptr;
	sf::Color m_color;
};

#endif // FREQVIEW_H
