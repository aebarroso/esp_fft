#ifndef REALTIMEFFT_H
#define REALTIMEFFT_H

#include <Arduino.h>
#include "fft.h"

class RealTimeFFT {
public:
    RealTimeFFT(float samplingFrequency, size_t sampleSize);

    void begin();
    void addSample(float value);
    void process();

private:
    float _samplingFrequency;
    size_t _sampleSize;

    float *_real;
    float *_imaginary;
    float *_magnitude;
    volatile int _bufferIndex;
    volatile bool _bufferFull;

    void computeAndPrintFFT();
};

#endif