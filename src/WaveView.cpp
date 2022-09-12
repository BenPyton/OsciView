#include "WaveView.h"
#include <math.h>

WaveView::WaveView(int x, int y, int width, int height, UIStyle& style)
	: AbstractUI(x, y, width, height, style)
{
	m_vertices = new sf::VertexArray(sf::PrimitiveType::Lines, width * 2);
}

WaveView::WaveView(const WaveView& _wv)
	: AbstractUI(_wv)
{
}

WaveView::WaveView(WaveView&& _wv)
	: AbstractUI(_wv)
{
	_wv.swap(*this);
}

WaveView::~WaveView()
{
	delete m_vertices;
}

WaveView& WaveView::operator=(WaveView&& _wv)
{
	_wv.swap(*this);
	return *this;
}

void WaveView::swap(WaveView& _other)
{
	AbstractUI::swap(_other);
	std::swap(m_samples, _other.m_samples);
	std::swap(m_vertices, _other.m_vertices);
	std::swap(m_sampleRate, _other.m_sampleRate);
}

void WaveView::setSamples(std::vector<sf::Int16>* _samples)
{
	m_samples = _samples;
}

void WaveView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);

	float samplePerPixel = static_cast<float>(m_sampleRate) * 0.01f / m_rect->getSize().x;

	//cout << "COUNT: " << m_samples->size() << endl;

	m_vertices->clear();
	float halfHeight = m_rect->getSize().y * 0.5f;
	sf::Int16 min, max;
	float x, yMin, yMax;
	for(int i = 0; i < m_rect->getSize().x; ++i)
	{
		getMinMax(round(i * samplePerPixel), round((i + 1) * samplePerPixel), min, max);
		x = i + m_rect->getPosition().x;
		yMin = m_rect->getPosition().y + halfHeight - halfHeight * min / static_cast<float>(INT16_MAX);
		yMax = m_rect->getPosition().y + halfHeight - halfHeight * max / static_cast<float>(INT16_MAX);
		m_vertices->append(sf::Vertex(sf::Vector2f(x, yMin)));
		m_vertices->append(sf::Vertex(sf::Vector2f(x, yMax)));
	}

	target.draw(*m_vertices, states);
}

void WaveView::_updateState()
{
	m_state = UIState::UI_NORMAL;
}

void WaveView::getMinMax(size_t start, size_t end, sf::Int16& outMin, sf::Int16& outMax) const
{
	outMin = INT16_MAX;
	outMax = INT16_MIN;

	sf::Int16 sample;
	for(int i = start; i <= end; ++i)
	{
		sample = (i < m_samples->size()) ? m_samples->at(i) : 0;
		if(sample < outMin)
			outMin = sample;
		if(sample > outMax)
			outMax = sample;
	}
}