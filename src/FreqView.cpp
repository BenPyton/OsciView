#include "FreqView.h"
#include <math.h>
#include "Core/Utils.h"
#include "FFTWrapper.h"

FreqView::FreqView(int x, int y, int width, int height, UIStyle& style)
	: AbstractUI(x, y, width, height, style)
{
	m_vertices = new sf::VertexArray(sf::PrimitiveType::Quads);
	m_color = sf::Color(200, 200, 200);
}

FreqView::FreqView(const FreqView& _fv)
	: AbstractUI(_fv)
{
}

FreqView::FreqView(FreqView&& _fv)
	: AbstractUI(_fv)
{
	_fv.swap(*this);
}

FreqView::~FreqView()
{
	delete m_vertices;
}

FreqView& FreqView::operator=(FreqView&& _fv)
{
	_fv.swap(*this);
	return *this;
}

void FreqView::swap(FreqView& _other)
{
	AbstractUI::swap(_other);
	std::swap(m_samples, _other.m_samples);
	std::swap(m_vertices, _other.m_vertices);
	std::swap(m_color, _other.m_color);
}

void FreqView::setSamples(const FrequencyBuffer& _samples)
{
	m_samples = &_samples;
}

void FreqView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);

	if (!getEnabled())
		return;

	if (m_samples == nullptr)
		return;

	size_t fftSize = FFT_SIZE / 2;
	size_t nbStep = 40;

	double a = 2595.0, b = 700.0;
	//double a = 1500, b = 50; // Mel scale param to look like foobar2000 default spectrum view

	double maxFreq = 8000.0;
	double maxMel = a * log10(1.0 + maxFreq / b);
	double melStep = maxMel / nbStep;

	m_vertices->resize(4 * nbStep);
	double stepFr = maxFreq / fftSize;

	float x, y, yBase = m_rect->getPosition().y + m_rect->getSize().y;
	float samplePerStep = fftSize / static_cast<float>(nbStep);
	float pixelPerStep = m_rect->getSize().x / static_cast<float>(nbStep);
	size_t sampleStart = 0, sampleEnd = 0;
	for(size_t i = 0; i < nbStep - 1; ++i)
	{
		double mel = b * (pow(10.0, melStep * (i + 1) / a) - 1);
		sampleStart = sampleEnd;
		sampleEnd = static_cast<size_t>(round(mel / stepFr));
		float value = 0.0;
		for(size_t k = sampleStart; k < sampleEnd; ++k)
		{
			value = max(value, m_samples->at(k));
		}

		x = i * pixelPerStep + m_rect->getPosition().x;
		y = yBase - 0.4f * static_cast<float>(log10(max(value, 1.f))) * m_rect->getSize().y;
		(*m_vertices)[4 * i + 0] = (sf::Vertex(sf::Vector2f(x, yBase), m_color));
		(*m_vertices)[4 * i + 1] = (sf::Vertex(sf::Vector2f(x, y), m_color));
		(*m_vertices)[4 * i + 2] = (sf::Vertex(sf::Vector2f(x + pixelPerStep - 1, y), m_color));
		(*m_vertices)[4 * i + 3] = (sf::Vertex(sf::Vector2f(x + pixelPerStep - 1, yBase), m_color));
	}

	target.draw(*m_vertices, states);
}

void FreqView::_updateState()
{
	m_state = UIState::UI_NORMAL;
}