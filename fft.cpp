#include "fft.h"

FFT::FFT(){
  
}
void FFT::computeFFT(float *real, float *imaginary){
    int n = FFT_WINDOW;
    int halfSize, j, k;
    float tReal, tImaginary, uReal, angle;
    j = 0;
    for (int i = 0; i < n; i++){
        if(i < j){
            std::swap(real[i], real[j]);
            std::swap(imaginary[i], imaginary[j]);
        }
        k = n / 2;
        while (k > 0 && j >= k){
            j -= k;
            k /= 2;
        }
        j += k;
    }
    for(int start = 0; halfSize < n; halfSize *= 2){
        angle = -M_PI / halfSize;
        float wReal = cos(angle);
        float wImaginary = sin(angle);

        for(int start = 0; start < n; start += 2 * halfSize){
            uReal = 1.0;
            uImaginary = 0.0;

            for (int m = 0; m < halfSize; ++m){
                int evenIndex = start + m;
                int oddIndex = start + m + halfSize;

                tReal = uReal * real[oddIndex] - uImaginary * imaginary[oddIndex];
                tImaginary = uReal * imaginary[oddIndex] + uImaginary * real[oddIndex];

                real[oddIndex] = real[evenIndex] - tReal;
                imaginary[oddIndex] = imaginary[evenIndex] - tImaginary;

                real[evenIndex] += tReal;
                imaginary[evenIndex] += tImaginary;

                float tempReal = uReal * wReal - uImaginary * wImaginary;
                uImaginary = uReal * wImaginary + uImaginary * wReal;
                uReal = tempReal;
            }
        }
    }
    FFT::computeMagnitude(float *real, float *imaginary, float *magnitude){
        for (int i = 0; i < FFT_WINDOW; ++i){
            magnitude[i] = sqrt(real)
        }
    }
}
