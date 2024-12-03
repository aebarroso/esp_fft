#ifndef REALTIMEFFT_H
#define REALTIMEFFT_H

#include <Arduino.h>
#include "fft.h"

class RealTimeFFT {
public:
    RealTimeFFT(uint8_t analogPin, float samplingFrequency, size_t sampleSize);

    void begin();
    void process();

private:
    uint8_t _analogPin;
    float _samplingFrequency;
    size_t _sampleSize;

    float *_real;
    float *_imaginary;
    float *_magnitude;
    volatile int _bufferIndex;
    volatile bool _bufferFull;

    void IRAM_ATTR onTimer();
    hw_timer_t *_timer;

    void computeAndPrintFFT();
};

#endif
