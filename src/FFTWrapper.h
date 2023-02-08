#ifndef FFTWRAPPER_H
#define FFTWRAPPER_H

#include "ffft/FFTRealFixLenParam.h"
#include <array>
#include <cstddef> // size_t

constexpr unsigned char FFT_POWER_OF_TWO = 10;
constexpr size_t FFT_SIZE = 1024;

using FFTType = ffft::FFTRealFixLenParam::DataType;
using TimeBuffer = std::array<FFTType, FFT_SIZE>;
using FrequencyBuffer = std::array<FFTType, FFT_SIZE / 2>;

class FFTWrapper final
{
public:
	FFTWrapper();
	~FFTWrapper();

	// Takes an input array (size FFT_SIZE) of time space values
	// Returns an output array (size FFT_SIZE/2) of frequency space values (magnitude of the complex numbers)
	void computeFFT(const TimeBuffer& in, FrequencyBuffer& out);

private:
	class FFTWrapperInstance* m_fft;
	FFTType m_outTmp[FFT_SIZE] = { 0 };
};

#endif // FFTWRAPPER_H
