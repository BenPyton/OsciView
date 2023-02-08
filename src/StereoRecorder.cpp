#include "StereoRecorder.h"
#include <iostream>
#include <cmath>
#include "Core/Utils.h"
#include "Types.h"

static TimeBuffer s_hanning;

void InitializeHanning()
{
	static bool initialized = false;
	if (!initialized)
	{
		for (size_t i = 0; i < FFT_SIZE; ++i)
		{
			s_hanning[i] = 0.5 - 0.5 * cos((i / static_cast<FFTType>(FFT_SIZE)) * 2 * PI_FFT);
		}
		initialized = true;
	}
}

StereoRecorder::StereoRecorder()
	: sf::SoundRecorder()
	, m_rightDataBuffer()
	, m_leftDataBuffer()
	, m_rightData()
	, m_leftData()
	, m_rightFreq()
	, m_leftFreq()
	, m_pos(0)
{
	setProcessingInterval(sf::milliseconds(10));

	InitializeHanning();
}

StereoRecorder::~StereoRecorder()
{
	stop();
}

void StereoRecorder::updateSamples()
{
	// Not thread safe for multiple stereo recorder!
	// But avoid allocating an array each frame
	static TimeBuffer timeSpace;

	for (size_t k = 0; k < FFT_SIZE; ++k)
	{
		timeSpace[k] = s_hanning[k] * m_leftData.at(k) / static_cast<FFTType>(INT16_MAX);
	}

	m_FFT.computeFFT(timeSpace, m_leftFreq);

	for (size_t k = 0; k < FFT_SIZE; ++k)
	{
		timeSpace[k] = s_hanning[k] * m_rightData.at(k) / static_cast<FFTType>(INT16_MAX);
	}

	m_FFT.computeFFT(timeSpace, m_rightFreq);
}

bool StereoRecorder::onProcessSamples(const sf::Int16* _samples, std::size_t _sampleCount)
{
	size_t maxSample = _sampleCount / 2;
	if (maxSample + m_pos > 2 * FFT_SIZE)
		maxSample = 2 * FFT_SIZE - m_pos;

	bool overflow = false;
	size_t nbSample = maxSample;

	if (m_pos + nbSample >= FFT_SIZE)
	{
		nbSample = FFT_SIZE - m_pos;
		overflow = true;
	}

	for (size_t i = 0; i < nbSample; ++i)
	{
		m_leftDataBuffer[m_pos + i] = _samples[2 * i];
		m_rightDataBuffer[m_pos + i] = _samples[2 * i + 1];
	}

	if (overflow)
	{
		// Swap buffers
		m_bufferMutex.lock();
		std::swap(m_leftDataBuffer, m_leftData);
		std::swap(m_rightDataBuffer, m_rightData);
		m_bufferMutex.unlock();

		// Fill the remaining samples
		for (size_t i = 0; i < maxSample - nbSample; ++i)
		{
			m_leftDataBuffer[i] = _samples[2 * (nbSample + i)];
			m_rightDataBuffer[i] = _samples[2 * (nbSample + i) + 1];
		}

		m_pos = maxSample - nbSample;
	}
	else
		m_pos += nbSample;

	return true;
}