//
// Created by Anika Torres Davalos on 4/29/2026.
//

#include "waveform.h"
#include <stdio.h>
#include <math.h>

void RMS (WaveformSample *array){

    FILE *output_fp = fopen("outcome/report.txt", "w");;

    double arms[3];
    double sum_sq[3];
    double sum_av[3] = {0.0, 0.0, 0.0};
    double DC_offset[3];

    double final_arms[30];
    double final_Vpk[30];
    double final_DC_offset[30];
    double data_clipping[30] = {0};
    double time_clipping[30] = {0};

    int cycles = 0;
    int anomaly = 0;
    int clipping_anomaly = 0;
    int *panomaly = &clipping_anomaly;
    int jcount_hunds = 0;

    data_cycle (output_fp, array, arms, sum_sq, sum_av, DC_offset, data_clipping, time_clipping, clipping_anomaly, final_DC_offset, cycles, anomaly, jcount_hunds, final_arms, final_Vpk, panomaly);

    final_print(output_fp, final_arms, final_Vpk, cycles, anomaly, clipping_anomaly, final_DC_offset, data_clipping, time_clipping);

    fclose(output_fp);
}


void data_cycle (FILE *output_fp, WaveformSample *array, double *arms, double *sum_sq, double *sum_av, double *DC_offset, double *data_clipping, double *time_clipping, int clipping_anomaly, double *final_DC_offset, int cycles, int anomaly, int jcount_hunds, double *final_arms, double *final_Vpk, int *panomaly){

    int n = 100;
        for(int j = 0; j < 10; j++){

            // create array to hold HIGH and LOW values
            double Low[3] = {1000.0, 1000.0, 1000.0};
            double High[3] = {-1000.0, -1000.0, -1000.0};

            for (int i = 0; i < n; i++) {
                int array_position = (cycles * n) + i;

                double PhaseV[3] = {array[array_position].phase_A_Vol, array[array_position].phase_B_Vol, array[array_position].phase_C_Vol};

                for (int f = 0; f<3; f++){
                    sum_sq[f] += PhaseV[f] * PhaseV[f];
                    sum_av[f] += PhaseV[f];

                    if (fabs(PhaseV[f]) >= 324.9 ){

                        data_clipping[*panomaly] = PhaseV[f];
                        time_clipping[*panomaly] = array[array_position].timeStamp;
                        (*panomaly)++;

                    }
                }

                Pk_Amplitude (PhaseV, Low, High);

            }

            RMS_Math (output_fp, arms, sum_sq, n, cycles, final_arms);
            Pk_Amplitude_Math (output_fp, Low, High, cycles, final_Vpk);
            DCOffset_Math (output_fp, DC_offset, sum_av, n, cycles, final_DC_offset);

            for (int q = 0; q<3; q++){
                sum_sq[q] = 0;
                sum_av[q] = 0;
                arms[q] = 0;
            }

            cycles ++; //Count in which cycle the code is in

    }

}


void Pk_Amplitude (double *PhaseV, double *Low, double *High){

    for (int f = 0; f<3; f++){

            if (PhaseV[f] > High[f]){ High[f] =  PhaseV[f]; }
            if (PhaseV[f] < Low[f]){ Low[f] =  PhaseV[f]; }

    }

}

void Pk_Amplitude_Math (FILE *output_fp, double *Low, double *High, int cycles, double *final_Vpk){

        for(int f = 0; f<3; f++){
            double Vpk[3];
            Vpk[f] = High[f] - Low[f];
            final_Vpk[(cycles * 3) + f] = Vpk[f];// so that all phases are recorded
        }

}

void RMS_Math (FILE *output_fp, double *arms, double *sum_sq, int n, int cycles, double *final_arms){

    for(int f = 0; f<3; f++){
        arms[f] = sqrt(sum_sq[f] / n);
        final_arms[(cycles * 3) + f] = arms[f];

    }

}

void DCOffset_Math (FILE *output_fp, double *DC_offset, double *sum_av, int n, int cycles, double *final_DC_offset){

    for(int f = 0; f<3; f++){
        DC_offset[f] = sum_av[f] / n;
        final_DC_offset[(cycles * 3) + f] = DC_offset[f];

    }

}

void final_print(FILE *output_fp, double *final_arms, double *final_Vpk, int cycles, int anomaly, int clipping_anomaly, double *final_DC_offset, double *data_clipping, double *time_clipping){

    char *titles[] = {"--- RMS Calculations---",
                      "\n\n--- Peak to Peak Amplitude ---",
                      "\n\n--- DC Offset ---",
                      "\n\n--- Clipping ---"};
    char *writing[] = {"\n  Cycle #%2d: Phase A = %lf V | Phase B = %lf V | Phase C = %lf V",
                       "\n  Cycle #%2d: Phase A = %lf VKp | Phase B = %lf VKp | Phase C = %lf VKp",
                       "\n  Cycle #%2d: Phase A = %lf V | Phase B = %lf V | Phase C = %lf V"};

    char phases[3] = {'A', 'B', 'C'};

    //first instance RMS
    fprintf(output_fp,"%s", titles[0]);
    for (int f = 0; f < 10; f++){

        int i = f * 3;
        fprintf(output_fp, writing[0], f + 1, final_arms[i], final_arms[i+1], final_arms[i+2]);

        for (int p = 0; p < 3; p++){

            if (final_arms[i + p] < 207 || final_arms[i + p] > 253) {
            fprintf(output_fp,
                    "\n\n  *** WARNING RSM Value out of 10%% Tolerance Range: ***\n       Phase %c, Cycle: #%d\n       RMS Value: %lf\n",
                    phases[p], f + 1, final_arms[i + p]);

            anomaly++;
        }

        }

    }

    if(anomaly == 0){// No tolerance errors
                fprintf(output_fp, "\n  No RMS Tolerance Errors\n");
            }

    //Second instance Peak to Peak
    fprintf(output_fp,"%s", titles[1]);
    for (int f = 0; f < 10; f++){

        int i = f * 3;
        fprintf(output_fp, writing[1], f + 1, final_Vpk[i], final_Vpk[i+1], final_Vpk[i+2]);
    }


    //third instance DC Offset
    fprintf(output_fp,"%s", titles[2]);
    for (int f = 0; f < 10; f++){

        int i = f * 3;
        fprintf(output_fp, writing[2], f + 1, final_DC_offset[i], final_DC_offset[i+1], final_DC_offset[i+2]);
    }

    //Four instance Clipping
    fprintf(output_fp,"%s", titles[3]);
    if (clipping_anomaly == 0){

        fprintf(output_fp, "\n No Clipping Values");
    }else{

        for (int i = 0; i < clipping_anomaly; i ++){
            fprintf(output_fp, "\n Time Stamp: %lf | Reading: %lf V", time_clipping[i], data_clipping[i]);
        }


    }
}

