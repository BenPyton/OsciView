#ifndef OSCIVIEW_H
#define OSCIVIEW_H

#include "UI/AbstractUI.h"
#include "Types.h"

class OsciView : public AbstractUI
{
public:
	OsciView(int x, int y, int width, int height, UIStyle& style = UIStyle::Default);
	OsciView(const OsciView& _ov);
	OsciView(OsciView&& _ov);
	virtual ~OsciView();
	OsciView& operator=(const OsciView& _ov) = delete;
	OsciView& operator=(OsciView&& _ov);
	void swap(OsciView& _other);

	void setSamples(const AudioBuffer& _leftSamples, const AudioBuffer& _rightSamples);
	void setColor(sf::Color _color) { m_color = _color; }
	void setIntensity(float _intensity) { m_intensity = _intensity; }
	void setLineWidth(float _lineWidth) { m_lineWidth = _lineWidth; }

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void _updateState() override;

private:
	const AudioBuffer* m_rightSamples = nullptr;
	const AudioBuffer* m_leftSamples = nullptr;
	sf::VertexArray* m_vertices = nullptr;
	sf::Shader* m_shader = nullptr;
	sf::Color m_color;
	float m_intensity = 1.0f;
	float m_lineWidth = 6.0f;
};

#endif // OSCIVIEW_H
