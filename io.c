#include <stdio.h>
#include "io.h"

void load_csv(WaveformSample *array){
    FILE *fp;

    fp = fopen("data/data_try.csv","r");

    if (fp == NULL){
        printf("Error: Cannot open file\n");
        return;
    }

    char line[256];

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp) !=NULL){
        sscanf(line,"%f %f %f %f %f %f %f",
               &array[0].timeStamp,
               &array[0].phase_A_Vol,
               &array[0].phase_B_Vol,
               &array[0].phase_C_Vol,
               &array[0].line_current,
               &array[0].frequency,
               &array[0].power_factor,
               &array[0].thd_percent);
    }

    FILE *output_fp = fopen("outcome/report.txt", "w");
    fprintf(output_fp, "Values: \n Time: %f\n Phase A: %f\n Phase B: %f\n",
            array[0].timeStamp,
            array[0].phase_A_Vol,
            array[0].phase_B_Vol,
            array[0].line_current,
            array[0].frequency,
            array[0].power_factor,
            array[0].thd_percent);
    fclose(output_fp);

    fclose(fp);

    return;
}



