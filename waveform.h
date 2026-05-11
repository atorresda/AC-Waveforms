//
// Created by Anika Torres Davalos on 4/29/2026.
//

#ifndef AC_WAVEFORMS_WAVEFORM_H
#define AC_WAVEFORMS_WAVEFORM_H

#include <math.h>
#include <stdio.h>

// RMS over one full cycle = 100 samples

typedef struct{
    double timeStamp; // every 0.0002 s
    double phase_A_Vol; //325.27 V peak = 230 V RMS * sqrt(2)
    double phase_B_Vol;
    double phase_C_Vol;
    double line_current; // Star connection. Tolerance, typical 3.5 A
    double frequency; // Cycles per second 50 Hz (10 complete cycles) (1 in 0.02 s)
    double power_factor;// Ratio real / apparent. 1.0 is ideal (0.95 typical)
    double thd_percent;//noise. 8% limit
}WaveformSample;

void RMS ();
void data_cycle (FILE *output_fp, WaveformSample *array, double *arms, double *sum_sq, double *sum_av, double *DC_offset, double *data_clipping, double *time_clipping, int clipping_anomaly, double *final_DC_offset, int cycles, int anomaly, int jcount_hunds, double *final_arms, double *final_Vpk, int *panomaly, char *clipping_phase);
void Pk_Amplitude (double *PhaseV, double *Low, double *High);
void Pk_Amplitude_Math (FILE *output_fp, double *Low, double *High, int cycles, double *final_Vpk);
void RMS_Math (FILE *output_fp, double *arms, double *sum_sq, int n, int cycles, double *final_arms);
void DCOffset_Math (FILE *output_fp, double *DC_offset, double *sum_sv, int n, int cycles, double *final_DC_offset);
void final_print(FILE *output_fp, double *final_arms, double *final_Vpk, int cycles, int anomaly, int clipping_anomaly, double *final_DC_offset, double *data_clipping, double *time_clipping, char *clipping_phase);

#endif //AC_WAVEFORMS_WAVEFORM_H
