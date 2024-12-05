#include "RealTimeFFT.h"

#define SAMPLE_FREQUENCY 1000
#define SAMPLE_SIZE 128

RealTimeFFT fftProcessor(SAMPLE_FREQUENCY, SAMPLE_SIZE);

void setup() {
    Serial.begin(115200);
    fftProcessor.begin();
}

void loop() {
    static unsigned long lastSampleTime = 0;
    unsigned long currentTime = micros();

    float sampleValue = sin(2 * PI * 50 * currentTime / 1000000.0);

    if (currentTime - lastSampleTime >= 1000000 / SAMPLE_FREQUENCY) {
        fftProcessor.addSample(sampleValue);
        lastSampleTime = currentTime;
    }

    fftProcessor.process();
}
