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

    int i = 0;
    while (fgets(line, sizeof(line), fp) !=NULL && i<29){
        sscanf(line,"%f,%f,%f,%f,%f,%f,%f,%f",
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
        fprintf(output_fp, "Values: \n Time: %f\n Phase A: %f\n Phase B: %f\n Phase C: %f\n Current: %f\n Frequency: %f\n Power Fac: %f\n THD percent: %f\n",
                array[0].timeStamp,
                array[1].phase_A_Vol,
                array[2].phase_B_Vol,
                array[3].phase_C_Vol,
                array[4].line_current,
                array[5].frequency,
                array[6].power_factor,
                array[27].thd_percent);
        fclose(output_fp);
    }

    fclose(fp);
}



