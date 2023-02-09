#ifndef WAVEVIEW_H
#define WAVEVIEW_H

#include "UI/AbstractUI.h"
#include <vector>

class WaveView : public AbstractUI
{
public:
	WaveView(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	WaveView(const WaveView& _wv);
	WaveView(WaveView&& _wv);
	virtual ~WaveView();
	WaveView& operator=(const WaveView& _wv) = delete;
	WaveView& operator=(WaveView&& _wv);
	void swap(WaveView& _other);

	void setSamples(std::vector<sf::Int16>* _samples);
	void setSampleRate(int _sampleRate) { m_sampleRate = _sampleRate; }

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void _updateState() override;

private:
	void getMinMax(size_t start, size_t end, sf::Int16& outMin, sf::Int16& outMax) const;

private:
	std::vector<sf::Int16>* m_samples = nullptr;
	sf::VertexArray* m_vertices = nullptr;
	int m_sampleRate = 0;
};

#endif // WAVEVIEW_H
