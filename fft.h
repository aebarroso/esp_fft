#ifndef FFT_H
#define FFT_H

#include <Arduino.h>
#include <cmath>

#define FFT_WINDOW 256

class FFT{
  public:
  FFT();
  void computeFFT(float *real, float *imaginary);
  void computeMagnitude(float *real, float *imaginary, float *magnitude);
};

#endif
