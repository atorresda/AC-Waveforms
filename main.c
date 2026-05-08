#include <stdio.h>
#include<stdlib.h>
#include "waveform.h"
#include "io.h"

int main() {

    int rows_number = 1001;
    WaveformSample *array;

    array = (WaveformSample *)malloc(rows_number * sizeof(WaveformSample));

    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    load_csv(array);

    free(array);

    return 0 ;
}