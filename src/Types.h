#ifndef TYPES_H
#define TYPES_H

#include <array>

// Includes base types (like sf::Int16)
#include <SFML/Config.hpp>

// Includes defines for FFT
#include "FFTWrapper.h"

using AudioBuffer = std::array<sf::Int16, FFT_SIZE>;

static const FFTType PI_FFT = static_cast<FFTType>(3.141592653589793238462643383279502884197169399375105820974944L);

#endif // TYPES_H
