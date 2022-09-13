#include "StereoRecorder.h"
#include <iostream>
#include "Core/Utils.h"

StereoRecorder::StereoRecorder()
	: sf::SoundRecorder()
	, m_rightBuffer()
	, m_leftBuffer()
	, m_rightDFT()
	, m_leftDFT()
	, m_DFTEnabled(true)
{
	setProcessingInterval(sf::milliseconds(8));
}

void StereoRecorder::updateSamples()
{
	m_bufferMutex.lock();
	std::swap(m_leftBuffer, m_leftSamples);
	std::swap(m_rightBuffer, m_rightSamples);
	m_bufferMutex.unlock();

	if (m_DFTEnabled)
	{
		std::vector<double> timeSpace(m_leftSamples.size());
		for (int k = 0; k < m_leftSamples.size(); ++k)
		{
			timeSpace[k] = m_leftSamples.at(k) / static_cast<double>(INT16_MAX);
		}

		// compute the frequency space samples
		DFT(timeSpace, m_leftDFT);

		timeSpace.resize(m_rightSamples.size());
		for (int k = 0; k < m_rightSamples.size(); ++k)
		{
			timeSpace[k] = m_rightSamples.at(k) / static_cast<double>(INT16_MAX);
		}

		DFT(timeSpace, m_rightDFT);
	}
	else
	{
		m_leftDFT.resize(0);
		m_rightDFT.resize(0);
	}
}

bool StereoRecorder::onProcessSamples(const sf::Int16* _samples, std::size_t _sampleCount)
{
	m_bufferMutex.lock();
	m_leftBuffer.resize(_sampleCount / 2);
	m_rightBuffer.resize(_sampleCount / 2);
	for(int i = 0; i < _sampleCount / 2; ++i)
	{
		m_leftBuffer[i] = _samples[2 * i];
		m_rightBuffer[i] = _samples[2 * i + 1];
	}
	m_bufferMutex.unlock();
	//std::cout << "Processed sample count: " << _sampleCount << " | left: " << m_leftBuffer.size() << " | right: " << m_rightBuffer.size() << std::endl;

	return true;
}