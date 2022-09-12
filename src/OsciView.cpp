#include "OsciView.h"
#include <math.h>
#include "Core/Utils.h"
#include <iomanip>

union ConversionFloatUInt32
{
	float floatValue;
	sf::Uint32 intValue;
};

OsciView::OsciView(int x, int y, int width, int height, UIStyle& style)
	: AbstractUI(x, y, width, height, style)
{
	m_vertices = new sf::VertexArray(sf::PrimitiveType::Quads);
	m_color = sf::Color(255, 255, 0);

	string frag = 
	"//FRAGMENT SHADER\
\n	#define TAUR 2.5066282746310002\
\n	#define EPS 1E-6\
\n	#define SQRT2 1.4142135623730951\
\n\
\n	uniform vec4 _Color;\
\n	uniform float _Intensity;\
\n\
\n	// A standard gaussian function, used for weighting samples\
\n	float gaussian(float x, float sigma)\
\n	{\
\n		return exp(-(x * x) / (2.0 * sigma * sigma)) / (TAUR * sigma);\
\n	}\
\n\
\n	// This approximates the error function, needed for the gaussian integral\
\n	float erf(float x)\
\n	{\
\n		float s = sign(x), a = abs(x);\
\n		x = 1.0 + (0.278393 + (0.230389 + 0.078108 * (a * a)) * a) * a;\
\n		x *= x;\
\n		return s - s / (x * x);\
\n	}\
\n\
\n	// decode a 4 uint8 color (little-endian) into a float value\
\n	float decodeFloat(vec4 color)\
\n	{\
\n		uint encodedFloat = uint(round(color.r * 256));\
\n		encodedFloat |= uint(round(color.g * 256) * pow(2, 8));\
\n		encodedFloat |= uint(round(color.b * 256) * pow(2, 16));\
\n		encodedFloat |= uint(round(color.a * 256) * pow(2, 24));\
\n		return uintBitsToFloat(encodedFloat);\
\n	}\
\n\
\n	void main()\
\n	{\
\n		float len = decodeFloat(gl_Color);\
\n		vec2 xy = gl_TexCoord[0].xy;\
\n		float alpha;\
\n\
\n		float sigma = 0.25f;\
\n		if(len < EPS)\
\n		{\
\n			// If the beam segment is too short, just calculate intensity at the position.\
\n			alpha = exp(-pow(length(xy), 2.0) / (2.0 * sigma * sigma)) / 2.0;\
\n		}\
\n		else\
\n		{\
\n			// Otherwise, use analytical integral for accumulated intensity.\
\n			alpha = erf(xy.x / SQRT2 / sigma) - erf((xy.x - len) / SQRT2 / sigma);\
\n			alpha *= exp(-xy.y * xy.y / (2.0 * sigma * sigma)) / 2.0 / len;\
\n		}\
\n\
\n		alpha *= _Intensity;\
\n		gl_FragColor = vec4(max(_Color.rgb, vec3(1./32., 1./32., 1./32.)), alpha);\
\n		//gl_FragColor = vec4(gl_TexCoord[0].xy, 0, 1);\
\n	}";



	m_shader = new sf::Shader();
	if(!m_shader->loadFromMemory(frag, sf::Shader::Fragment))
	{
		cerr << "Error while loading fragment shader" << endl;
		m_shader = nullptr;
	}
}

OsciView::OsciView(const OsciView& _ov)
	: AbstractUI(_ov)
{
}

OsciView::OsciView(OsciView&& _ov)
	: AbstractUI(_ov)
{
	_ov.swap(*this);
}

OsciView::~OsciView()
{
	delete m_vertices;
	delete m_shader;
}

OsciView& OsciView::operator=(OsciView&& _ov)
{
	_ov.swap(*this);
	return *this;
}

void OsciView::swap(OsciView& _other)
{
	AbstractUI::swap(_other);
	std::swap(m_leftSamples, _other.m_leftSamples);
	std::swap(m_rightSamples, _other.m_rightSamples);
	std::swap(m_vertices, _other.m_vertices);
}

void OsciView::setSamples(std::vector<sf::Int16>* _leftSamples, std::vector<sf::Int16>* _rightSamples)
{
	m_leftSamples = _leftSamples;
	m_rightSamples = _rightSamples;
}

void OsciView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);

	// 4 vertex per line (lines are quads)
	m_vertices->resize(4 * (m_leftSamples->size()));
	float halfWidth = m_rect->getSize().x * 0.5f;
	float halfHeight = m_rect->getSize().y * 0.5f;

	float sigma = 0.4f;
	float a = 1.0f / (sigma * _SQRT2PI);
	float b = -1.0f / (2 * sigma * sigma);
	float lineHalfWidth = m_lineWidth * 0.5f;;

	sf::Vector2f p1, p2, right, up;
	ConversionFloatUInt32 unionLength;
	sf::Color encodedLength;

	if(m_shader != nullptr)
	{
		m_shader->setUniform("_Color", static_cast<sf::Glsl::Vec4>(m_color));
		m_shader->setUniform("_Intensity", m_intensity);
	}

	for(int i = 0; i < m_leftSamples->size(); ++i)
	{
		p2.x = m_rect->getPosition().x + halfWidth + halfWidth * m_leftSamples->at(i) / static_cast<float>(INT16_MAX);
		p2.y = m_rect->getPosition().y + halfHeight - halfHeight * m_rightSamples->at(i) / static_cast<float>(INT16_MAX);
		if(i > 0)
		{
			float l = length(p2.x - p1.x, p2.y - p1.y);
			right = lineHalfWidth * (p2 - p1) / l;
			up.x = -right.y;
			up.y = right.x;

			// tricky part : I use the vertex color to pass the line length to the fragment shader
			unionLength.floatValue = l / lineHalfWidth;
			encodedLength.r = unionLength.intValue & 0xFF;
			encodedLength.g = (unionLength.intValue >> 8) & 0xFF;
			encodedLength.b = (unionLength.intValue >> 16) & 0xFF;
			encodedLength.a = (unionLength.intValue >> 24) & 0xFF;

			(*m_vertices)[4 * i + 1] = sf::Vertex(p1 - right - up, encodedLength, sf::Vector2f(-1.f, -1.f));
			(*m_vertices)[4 * i + 0] = sf::Vertex(p1 - right + up, encodedLength, sf::Vector2f(-1.f, 1.f));
			(*m_vertices)[4 * i + 3] = sf::Vertex(p2 + right - up, encodedLength, sf::Vector2f(unionLength.floatValue + 1.f, -1.f));
			(*m_vertices)[4 * i + 2] = sf::Vertex(p2 + right + up, encodedLength, sf::Vector2f(unionLength.floatValue + 1.f, 1.f));
		}
		p1.x = p2.x;
		p1.y = p2.y;
	}

	sf::RenderStates state(m_shader);
	state.blendMode = sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One, sf::BlendMode::Add);
	target.draw(*m_vertices, state);
}

void OsciView::_updateState()
{
	m_state = UIState::UI_NORMAL;
}
