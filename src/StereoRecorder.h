#ifndef _STEREORECORDER_H
#define _STEREORECORDER_H

#include <SFML/Audio/SoundRecorder.hpp>
#include <vector>
#include <mutex>

class StereoRecorder : public sf::SoundRecorder
{
public:
	StereoRecorder();

	std::vector<sf::Int16>* getRightSamples() { return &m_rightSamples; }
	std::vector<sf::Int16>* getLeftSamples() { return &m_leftSamples; }

	std::vector<double>* getRightDFT() { return &m_rightDFT; }
	std::vector<double>* getLeftDFT() { return &m_leftDFT; }

	// Method called in main thread loop to swap buffers
	void updateSamples();

	inline void enableDFT(bool enable) { m_DFTEnabled = enable; }
	inline bool DFTEnabled() const { return m_DFTEnabled; }

protected:
	virtual bool onProcessSamples(const sf::Int16* _samples, std::size_t _sampleCount) override;

private:
	std::mutex m_bufferMutex;
	// Buffers used in recorder thread
	std::vector<sf::Int16> m_rightBuffer;
	std::vector<sf::Int16> m_leftBuffer;

	// Buffers used in main thread (by external code)
	std::vector<sf::Int16> m_rightSamples;
	std::vector<sf::Int16> m_leftSamples;

	// Buffers storing frequency domain
	std::vector<double> m_rightDFT;
	std::vector<double> m_leftDFT;

	bool m_DFTEnabled;
};

#endif // _STEREORECORDER_H
