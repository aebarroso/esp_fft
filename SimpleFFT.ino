#include <Arduino.h>
#include "RealTimeFFT.h"

#define ANALOG_PIN A0
#define SAMPLING_FREQUENCY 1000
#define SAMPLE_SIZE 256

RealTimeFFT realTimeFFT(ANALOG_PIN, SAMPLING_FREQUENCY, SAMPLE_SIZE);

void setup() {
    Serial.begin(115200);
    realTimeFFT.begin();
}

void loop() {
    realTimeFFT.process();
}
