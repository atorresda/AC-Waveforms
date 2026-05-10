//
// Created by Anika Torres Davalos on 4/29/2026.
//

#include "waveform.h"
#include <stdio.h>
#include <math.h>

void RMS (WaveformSample *array){

    FILE *output_fp;

    double arms[3];
    double sum_sq[3];

    double final_arms[10];
    double final_Vpk[10];

    int cycles = 0;
    int anomaly = 0;
    int jcount_hunds = 0;

    data_cycle (output_fp, array, arms, sum_sq, cycles, anomaly, jcount_hunds, final_arms, final_Vpk);

    if(anomaly == 0){ // No tolerance errors
        output_fp = fopen("outcome/report.txt", "a");
        if (output_fp == NULL){

            printf("Error:Couldn't create report.txt\n");

        }else {
            fprintf(output_fp, "\n  No RMS Tolerance Errors\n");
            fclose(output_fp);
        }
    }

    final_print(output_fp, final_arms, final_Vpk, cycles);

}


void data_cycle (FILE *output_fp, WaveformSample *array, double *arms, double *sum_sq, int cycles, int anomaly, int jcount_hunds, double *final_arms, double *final_Vpk){

        for(int j = 0; j < 1000; j++){

        if(j == jcount_hunds) {
            jcount_hunds += 100;

            // create array to hold HIGH and LOW values
            double Low[3] = {1000.0, 1000.0, 1000.0};
            double High[3] = {-1000.0, -1000.0, -1000.0};

            int n = 100;
            for (int i = 0; i < n; i++) {
                int array_position = (cycles * n) + i;

                double PhaseV[3] = {array[array_position].phase_A_Vol, array[array_position].phase_B_Vol, array[array_position].phase_C_Vol};

                for (int f = 0; f<3; f++){
                    sum_sq[f] += PhaseV[f] * PhaseV[f];
                }

                Pk_Amplitude (PhaseV, Low, High);

            }

            RMS_Math (output_fp, arms, sum_sq, n, cycles, final_arms);
            Pk_Amplitude_Math (output_fp, Low, High, cycles, final_Vpk);

            if (arms[0] < 207 || arms[0] > 253) { // +-10% of 230 = 207:253
                output_fp = fopen("outcome/report.txt", "a");
                if (output_fp == NULL) {

                    printf("Error:Couldn't create report.txt\n");

                } else {
                    fprintf(output_fp,
                            "\n\n  *** WARNING RSM Value out of 10% Tolerance Range: ***\n       Phase A, Cycle: #%d\n       Time Stamp: %lf\n       RMS Value: %lf\n",
                            cycles + 1, array[j].timeStamp, arms[0]);
                    fclose(output_fp);
                    anomaly++;
                }
            }

            if (arms[1] < 207 || arms[1] > 253) { // +-10% of 230 = 207:253
                output_fp = fopen("outcome/report.txt", "a");
                if (output_fp == NULL) {

                    printf("Error:Couldn't create report.txt\n");

                } else {
                    fprintf(output_fp,
                            "\n  WARNING RSM Value out of 10% Tolerance Range: \n   Phase B, Cycle: #%d\n   Time Stamp: %lf\n   RMS Value: %lf\n",
                            cycles + 1, array[j].timeStamp, arms[1]);
                    fclose(output_fp);
                    anomaly++;
                }
            }

            if (arms[2] < 207 || arms[2] > 253) { // +-10% of 230 = 207:253
                output_fp = fopen("outcome/report.txt", "a");
                if (output_fp == NULL) {

                    printf("Error:Couldn't create report.txt\n");

                } else {
                    fprintf(output_fp,
                            "\n  WARNING RSM Value out of 10% Tolerance Range: \n   Phase C, Cycle: #%d\n   Time Stamp: %lf\n   RMS Value: %lf\n",
                            cycles + 1, array[j].timeStamp, arms[2]);
                    fclose(output_fp);
                    anomaly++;
                }
            }

            for (int q = 0; q<3; q++){
                sum_sq[q] = 0;
                arms[q] = 0;
            }

            cycles ++; //Count in which cycle the code is in
        }

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
            final_Vpk[f] = Vpk[f];
        }

}

void RMS_Math (FILE *output_fp, double *arms, double *sum_sq, int n, int cycles, double *final_arms){

    for(int f = 0; f<3; f++){
        arms[f] = sqrt(sum_sq[f] / n);
        final_arms[f] = arms[f];
    }

}

void final_print(FILE *output_fp, double *final_arms, double *final_Vpk, int cycles){

    output_fp = fopen("outcome/report.txt", "w");

    for (int f = 0; f < 10; f++){

        int i = 0;
        fprintf(output_fp,"---RMS Calculations---"
                      "\n  Cycle #%d: Phase A = %.4lf V | Phase B = %.4lf V | Phase C = %.4lf V", f + 1, final_arms[i], final_arms[i+1], final_arms[i+2]);

        fprintf(output_fp, "\n\n---Peak to Peak Amplitude ---"
                       "\n  Cycle #%d: Phase A = %lf VKp | Phase B = %lf VKp | Phase C = %lf VKp", f + 1, final_Vpk[i], final_Vpk[i+1], final_Vpk[i+2]);

        i += 3;

    }


    fclose(output_fp);

}

