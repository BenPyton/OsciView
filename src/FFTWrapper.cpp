#include "FFTWrapper.h"
#include "ffft/FFTRealFixLen.h"

class FFTWrapperInstance : public ffft::FFTRealFixLen<FFT_POWER_OF_TWO> {};

FFTWrapper::FFTWrapper()
	: m_fft(new FFTWrapperInstance)
{
}

FFTWrapper::~FFTWrapper()
{
	delete m_fft;
}

void FFTWrapper::computeFFT(const TimeBuffer& in, FrequencyBuffer& out)
{
	m_fft->do_fft(m_outTmp, in.data());

	FFTType real;
	FFTType imag;
	for (size_t i = 0; i < FFT_SIZE / 2; ++i)
	{
		real = m_outTmp[i];
		imag = m_outTmp[FFT_SIZE / 2 + i];
		out[i] = sqrt(real * real + imag * imag);
	}
}