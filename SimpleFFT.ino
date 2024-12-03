#include <Arduino.h>
#include "fft.h"

#define SAMPLE_SIZE FFT_WINDOW

float real[SAMPLE_SIZE];
float imaginary[SAMPLE_SIZE];
float magnitude[SAMPLE_SIZE];

FFT fft;

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < SAMPLE_SIZE; i++) {
        real[i] = sin(2 * M_PI * i / SAMPLE_SIZE);
        imaginary[i] = 0.0; 
    }

    fft.computeFFT(real, imaginary);
    fft.computeMagnitude(real, imaginary, magnitude);
    
    for (int i = 0; i < SAMPLE_SIZE / 2; i++) { 
        Serial.printf("Frequency bin %d: Magnitude = %.2f\n", i, magnitude[i]);
    }
}

void loop() {
    
}
