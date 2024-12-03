#include "RealTimeFFT.h"

RealTimeFFT::RealTimeFFT(uint8_t analogPin, float samplingFrequency, size_t sampleSize)
    : _analogPin(analogPin),
      _samplingFrequency(samplingFrequency),
      _sampleSize(sampleSize),
      _bufferIndex(0),
      _bufferFull(false) {

    _real = new float[sampleSize];
    _imaginary = new float[sampleSize];
    _magnitude = new float[sampleSize];
}

void RealTimeFFT::begin() {
    pinMode(_analogPin, INPUT);

    _timer = timerBegin(0, 80, true);
    timerAttachInterrupt(_timer, [this]() { this->onTimer(); }, true);
    timerAlarmWrite(_timer, 1000000 / _samplingFrequency, true);
    timerAlarmEnable(_timer);

    Serial.println("Real-time FFT setup complete.");
}

void IRAM_ATTR RealTimeFFT::onTimer() {
    _real[_bufferIndex] = analogRead(_analogPin) / 1023.0; // Normalize to 0-1 range
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
