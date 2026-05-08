#include <stdio.h>
#include "waveform.h"
#include "io.h"

int main() {
    WaveformSample array[2];
    load_csv(array);

    return 0 ;
}