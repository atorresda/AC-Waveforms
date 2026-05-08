#include <stdio.h>
#include "io.h"

void load_csv(WaveformSample *array){
    FILE *fp;

    fp = fopen("data/data_try.csv","r");

    if (fp == NULL){
        printf("Error: Cannot open file\n");
        return 1;
    }

    char line[256];

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp) !=NULL){
        sscanf(fp,"%f %f %f", array[0]);
    }

    FILE *output_fp = fopen("outcome/report.txt", "w");
    fprintf("Values: \n Time: %f\n Phase A: %f\n Phase B: %f\n",
            array[0].timeStamp,
            array[0].phase_A_Vol,
            array[0].phase_B_Vol)'];
    fclose(output_fp);

    fclose(fp);

    return 0;
}



