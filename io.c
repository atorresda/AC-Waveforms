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

    fclose(fp);
}



