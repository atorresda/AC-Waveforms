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

    double Aarms;
    double Barms;
    double Carms;

    int anomaly = 0;

    for(int j = 0; j < 1000; j++){

        int cycles = 1;

        int n = 100;
        for (int i = 0; i < n; i++) {
            Asum_sq += array[i].phase_A_Vol * array[i].phase_A_Vol;
            Bsum_sq += array[i].phase_B_Vol * array[i].phase_B_Vol;
            Csum_sq += array[i].phase_C_Vol * array[i].phase_C_Vol;
        }
        Aarms = sqrt(Asum_sq / n);
        Barms = sqrt(Bsum_sq / n);
        Carms = sqrt(Csum_sq / n);

        if(Aarms < 207 || Aarms > 253){ // +-10% of 230 = 207:253
            output_fp = fopen("outcome/report.txt", "w");
            if (output_fp == NULL){

                printf("Error:Couldn't create report.txt\n");

            }else {
                fprintf(output_fp, "WARNING RSM Value out of 10% Tolerance Range: \n Phase A, Cycle: #%d\n Time Stamp: %lf\n RMS Value: %lf\n", cycles, array[j].timeStamp, Aarms);
                fclose(output_fp);
                anomaly ++;
            }
        }

        if(Barms < 207 || Barms > 253){ // +-10% of 230 = 207:253
            output_fp = fopen("outcome/report.txt", "w");
            if (output_fp == NULL){

                printf("Error:Couldn't create report.txt\n");

            }else {
                fprintf(output_fp, "WARNING RSM Value out of 10% Tolerance Range: \n Phase B, Cycle: #%d\n Time Stamp: %lf\n RMS Value: %lf\n", cycles, array[j].timeStamp, Barms);
                fclose(output_fp);
                anomaly ++;
            }
        }

        if(Carms < 207 || Carms > 253){ // +-10% of 230 = 207:253
            output_fp = fopen("outcome/report.txt", "w");
            if (output_fp == NULL){

                printf("Error:Couldn't create report.txt\n");

            }else {
                fprintf(output_fp, "WARNING RSM Value out of 10% Tolerance Range: \n Phase C, Cycle: #%d\n Time Stamp: %lf\n RMS Value: %lf\n", cycles, array[j].timeStamp, Carms);
                fclose(output_fp);
                anomaly ++;
            }
        }

        Asum_sq = 0;
        Bsum_sq = 0;
        Csum_sq = 0;
        Aarms = 0;
        Barms = 0;
        Carms = 0;

        n = 0;

        int p = 1;

        if(j/p == 10){cycles ++;} //Count in which cycle the code is in
        p += 0.01;

    }

    if(anomaly == 0){ // No tolerance errors
        output_fp = fopen("outcome/report.txt", "a");
        if (output_fp == NULL){

            printf("Error:Couldn't create report.txt\n");

        }else {
            fprintf(output_fp, "No RMS Tolerance Erros\n");
            fclose(output_fp);
        }
    }


}


