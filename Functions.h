//
// Created by Anika Torres Davalos on 4/29/2026.
//

#ifndef AC_WAVEFORMS_FUNCTIONS_H
#define AC_WAVEFORMS_FUNCTIONS_H

typedef struct{
    float timeStamp; // every 0.0002 s
    float phase_A_Vol; //
    float phase_B_Vol;
    float phase_C_Vol;
    float line_current;
    float frequency;
    float power_factor;
    float thd_percent;
}WaveformSample;







#endif //AC_WAVEFORMS_FUNCTIONS_H
