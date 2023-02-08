#include "SpectrumView.h"
#include <math.h>
#include "Core/Utils.h"

SpectrumView::SpectrumView(int x, int y, int width, int height, UIStyle& style)
	: AbstractUI(x, y, width, height, style)
{
	m_color = sf::Color(200, 200, 200);

	m_tex = new sf::Texture();
	m_tex->create(width, 50);
	m_tex->setSmooth(true);
	m_tex->setRepeated(true);

	m_spr = new sf::Sprite();
	m_spr->setTexture(*m_tex, true);

	m_img = new sf::Image();
	m_img->create(width, 50);
	m_currentIndex = 0;
}

SpectrumView::SpectrumView(const SpectrumView& _fv)
	: AbstractUI(_fv)
{
}

SpectrumView::SpectrumView(SpectrumView&& _fv)
	: AbstractUI(_fv)
{
	_fv.swap(*this);
}

SpectrumView::~SpectrumView()
{
	delete m_spr;
	delete m_tex;
	delete m_img;
}

SpectrumView& SpectrumView::operator=(SpectrumView&& _fv)
{
	_fv.swap(*this);
	return *this;
}

void SpectrumView::swap(SpectrumView& _other)
{
	AbstractUI::swap(_other);
	std::swap(m_samples, _other.m_samples);
	std::swap(m_tex, _other.m_tex);
	std::swap(m_img, _other.m_img);
	std::swap(m_spr, _other.m_spr);
	std::swap(m_color, _other.m_color);
}

void SpectrumView::setSamples(const FrequencyBuffer& _samples)
{
	m_samples = &_samples;
}

void SpectrumView::update()
{
	AbstractUI::update();

	if (!getEnabled())
		return;

	if (m_samples->size() <= 0)
		return;

	size_t fftSize = FFT_SIZE / 2;
	size_t nbStep = 50;

	double a = 2595.0, b = 700.0;
	//double a = 1500, b = 50; // Mel scale param to look like foobar2000 default spectrum view

	double maxFreq = 8000.0;
	double maxMel = a * log10(1.0 + maxFreq / b);
	double melStep = maxMel / nbStep;

	double stepFr = maxFreq / fftSize;

	float pixelPerStep = m_rect->getSize().x / static_cast<float>(nbStep);
	size_t sampleStart = 0, sampleEnd = 0;
	for (size_t i = 0; i < nbStep - 1; ++i)
	{
		double mel = b * (pow(10.0, melStep * (i + 1) / a) - 1);
		sampleStart = sampleEnd;
		sampleEnd = static_cast<size_t>(round(mel / stepFr));
		float value = 0.0;
		for (size_t k = sampleStart; k < sampleEnd; ++k)
		{
			value = max(value, m_samples->at(k));
		}
		
		m_img->setPixel(m_currentIndex, m_img->getSize().y - i - 1, lerp(sf::Color::White, sf::Color::Black, 0.4f * log10(max(value, 1.f))));
	}

	m_tex->update(*m_img);

	m_currentIndex++;
	if (m_currentIndex >= m_img->getSize().x)
	{
		m_currentIndex = 0;
	}

	m_spr->setPosition(getRealPosition());
	m_spr->setScale(sf::Vector2f(getRealSize().x / m_tex->getSize().x, getRealSize().y / m_tex->getSize().y));
	m_spr->setTextureRect(sf::IntRect(m_currentIndex, 0, m_img->getSize().x, m_img->getSize().y));
}

void SpectrumView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);

	if (!getEnabled())
		return;

	target.draw(*m_spr, states);
}

void SpectrumView::_updateState()
{
	m_state = UIState::UI_NORMAL;
}