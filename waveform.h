//
// Created by Anika Torres Davalos on 4/29/2026.
//

#ifndef AC_WAVEFORMS_WAVEFORM_H
#define AC_WAVEFORMS_WAVEFORM_H

#include <math.h>
#include <stdio.h>

// RMS over one full cycle = 100 samples

typedef struct{
    float timeStamp; // every 0.0002 s
    float phase_A_Vol; //325.27 V peak = 230 V RMS * sqrt(2)
    float phase_B_Vol;
    float phase_C_Vol;
    float line_current; // Star connection. Tolerance, typical 3.5 A
    float frequency; // Cycles per second 50 Hz (10 complete cycles) (1 in 0.02 s)
    float power_factor;// Ratio real / apparent. 1.0 is ideal (0.95 typical)
    float thd_percent;//noise. 8% limit
}WaveformSample;

#endif //AC_WAVEFORMS_WAVEFORM_H
