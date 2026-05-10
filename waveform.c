//
// Created by Anika Torres Davalos on 4/29/2026.
//

#include "waveform.h"
#include <stdio.h>
#include <math.h>

void RMS (WaveformSample *array){

    double Asum_sq = 0.0;
    double Bsum_sq = 0.0;
    double Csum_sq = 0.0;

    FILE *output_fp;
    output_fp = fopen("outcome/report.txt", "w");
    fprintf(output_fp,"---RMS Calculations---");
    fclose(output_fp);

    double Aarms;
    double Barms;
    double Carms;

    int cycles = 0;
    int anomaly = 0;
    int jcount_hunds = 0;

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

                // calculate sum of square root
                Asum_sq += PhaseV[0] * PhaseV[0];
                Bsum_sq += PhaseV[1] * PhaseV[1];
                Csum_sq += PhaseV[2] * PhaseV[2];

                Pk_Amplitude (PhaseV, Low, High);

            }

            Aarms = sqrt(Asum_sq / n);
            Barms = sqrt(Bsum_sq / n);
            Carms = sqrt(Csum_sq / n);

            output_fp = fopen("outcome/report.txt", "a");
            fprintf(output_fp, "\n  Cycle #%d: Phase A = %.4lf V | Phase B = %.4lf V | Phase C = %.4lf V", cycles + 1, Aarms, Barms, Carms);
            fclose(output_fp);

            Pk_Amplitude_Print (output_fp, Low, High, cycles);

            if (Aarms < 207 || Aarms > 253) { // +-10% of 230 = 207:253
                output_fp = fopen("outcome/report.txt", "a");
                if (output_fp == NULL) {

                    printf("Error:Couldn't create report.txt\n");

                } else {
                    fprintf(output_fp,
                            "\n\n  *** WARNING RSM Value out of 10% Tolerance Range: ***\n       Phase A, Cycle: #%d\n       Time Stamp: %lf\n       RMS Value: %lf\n",
                            cycles + 1, array[j].timeStamp, Aarms);
                    fclose(output_fp);
                    anomaly++;
                }
            }

            if (Barms < 207 || Barms > 253) { // +-10% of 230 = 207:253
                output_fp = fopen("outcome/report.txt", "a");
                if (output_fp == NULL) {

                    printf("Error:Couldn't create report.txt\n");

                } else {
                    fprintf(output_fp,
                            "\n  WARNING RSM Value out of 10% Tolerance Range: \n   Phase B, Cycle: #%d\n   Time Stamp: %lf\n   RMS Value: %lf\n",
                            cycles + 1, array[j].timeStamp, Barms);
                    fclose(output_fp);
                    anomaly++;
                }
            }

            if (Carms < 207 || Carms > 253) { // +-10% of 230 = 207:253
                output_fp = fopen("outcome/report.txt", "a");
                if (output_fp == NULL) {

                    printf("Error:Couldn't create report.txt\n");

                } else {
                    fprintf(output_fp,
                            "\n  WARNING RSM Value out of 10% Tolerance Range: \n   Phase C, Cycle: #%d\n   Time Stamp: %lf\n   RMS Value: %lf\n",
                            cycles + 1, array[j].timeStamp, Carms);
                    fclose(output_fp);
                    anomaly++;
                }
            }

            Asum_sq = 0;
            Bsum_sq = 0;
            Csum_sq = 0;
            Aarms = 0;
            Barms = 0;
            Carms = 0;

            cycles ++; //Count in which cycle the code is in
        }

    }

    if(anomaly == 0){ // No tolerance errors
        output_fp = fopen("outcome/report.txt", "a");
        if (output_fp == NULL){

            printf("Error:Couldn't create report.txt\n");

        }else {
            fprintf(output_fp, "\n  No RMS Tolerance Errors\n");
            fclose(output_fp);
        }
    }
}


void Pk_Amplitude (double *PhaseV, double *Low, double *High){

    for (int f = 0; f<3; f++){

            if (PhaseV[f] > High[f]){ High[f] =  PhaseV[f]; }
            if (PhaseV[f] < Low[f]){ Low[f] =  PhaseV[f]; }

    }

}

void Pk_Amplitude_Print (FILE *output_fp, double *Low, double *High, int cycles){

    double Vpk[3] = {High[0] - Low[0], High[1] - Low[1], High[2] - Low[2]};

    output_fp = fopen("outcome/report.txt", "a");
    fprintf(output_fp, "\n\n---Peak to Peak Amplitude ---"
                       "\n  Cycle #%d: Phase A = %lf VKp | Phase B = %lf VKp | Phase C = %lf VKp", cycles + 1, Vpk[0], Vpk[1], Vpk[2]);
    fclose(output_fp);

}

