#include "fft.h"

RealTimeFFT::RealTimeFFT(float samplingFrequency, size_t sampleSize)
    : _samplingFrequency(samplingFrequency),
      _sampleSize(sampleSize),
      _bufferIndex(0),
      _bufferFull(false) {
    _real = new float[sampleSize]();
    _imaginary = new float[sampleSize]();
    _magnitude = new float[sampleSize / 2]();
}

void RealTimeFFT::begin() {
    Serial.println("Real-time FFT setup complete.");
}

void RealTimeFFT::addSample(float value) {
    _real[_bufferIndex] = value;
    _imaginary[_bufferIndex] = 0.0;

    _bufferIndex++;
    if (_bufferIndex >= _sampleSize) {
        _bufferFull = true;
        _bufferIndex = 0;
    }
}

void RealTimeFFT::process() {
    if (_bufferFull) {
        _bufferFull = false;
        computeAndPrintFFT();
    }
}

void RealTimeFFT::computeAndPrintFFT() {
    FFT fft;
    fft.computeFFT(_real, _imaginary);

    fft.computeMagnitude(_real, _imaginary, _magnitude);

    for (size_t i = 0; i < _sampleSize / 2; i++) {
        float frequency = (i * _samplingFrequency) / _sampleSize;
        Serial.printf("Frequency: %.1f Hz, Magnitude: %.2f\n", frequency, _magnitude[i]);
    }
}

RealTimeFFT::~RealTimeFFT() {
    delete[] _real;
    delete[] _imaginary;
    delete[] _magnitude;
}
