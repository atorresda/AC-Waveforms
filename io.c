#include <stdio.h>
#include "io.h"

void load_csv(WaveformSample *array){
    FILE *fp;

    fp = fopen("data/power_quality_log.csv","r");

    if (fp == NULL){
        printf("Error: Cannot open file\n");
        return;
    }

    char line[256];

    fgets(line, sizeof(line), fp); // skip header

    int i = 0;
    while (fgets(line, sizeof(line), fp) !=NULL && i<1002){
        sscanf(line,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &array[i].timeStamp,
               &array[i].phase_A_Vol,
               &array[i].phase_B_Vol,
               &array[i].phase_C_Vol,
               &array[i].line_current,
               &array[i].frequency,
               &array[i].power_factor,
               &array[i].thd_percent);
        i++;
    }

    FILE *output_fp = fopen("outcome/report.txt", "w");
    if (output_fp == NULL){

        printf("Error:Couldn't create report.txt\n");

    }else {
        fprintf(output_fp, "Values: \n Time: %lf\n Phase A: %lf\n Phase B: %lf\n Phase C: %lf\n Current: %lf\n Frequency: %lf\n Power Fac: %lf\n THD percent: %lf\n",
                array[0].timeStamp,
                array[3].phase_A_Vol,
                array[50].phase_B_Vol,
                array[490].phase_C_Vol,
                array[598].line_current,
                array[800].frequency,
                array[801].power_factor,
                array[999].thd_percent);
        fclose(output_fp);
    }

    fclose(fp);
}



