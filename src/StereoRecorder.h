#ifndef STEREORECORDER_H
#define STEREORECORDER_H

#include <SFML/Audio/SoundRecorder.hpp>
#include <vector>
#include <mutex>
#include <atomic>
#include "Types.h"

class StereoRecorder : public sf::SoundRecorder
{
public:
	StereoRecorder();
	virtual ~StereoRecorder();

	const FrequencyBuffer& getRightFFT() { return m_rightFreq; }
	const FrequencyBuffer& getLeftFFT() { return m_leftFreq; }

	const AudioBuffer& getRightBuffer() const { return m_rightData; }
	const AudioBuffer& getLeftBuffer() const { return m_leftData; }

	// Method called in main thread loop to swap buffers
	void updateSamples();

protected:
	virtual bool onProcessSamples(const sf::Int16* _samples, std::size_t _sampleCount) override;

private:
	std::mutex m_bufferMutex;

	// Buffers used in recorder thread
	AudioBuffer m_rightDataBuffer;
	AudioBuffer m_leftDataBuffer;

	// Buffers used in main thread (by external code)
	AudioBuffer m_rightData;
	AudioBuffer m_leftData;

	FrequencyBuffer m_rightFreq;
	FrequencyBuffer m_leftFreq;

	FFTWrapper m_FFT;

	size_t m_pos;

	std::atomic<bool> m_bufferOverflow;
};

#endif // STEREORECORDER_H
