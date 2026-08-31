#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "motor.h"


int main(int argc, char *argv[]) {

    //where is the input coming from? terminal for now?
    //terminal for now: direction, duty_cycle, period_ms

    if (argc != 4) {
    printf("error, please input 3 numbers: direction (0,1), duty, period (in ms)");
    return 1;
    }

    int direction = atoi(argv[1]);
    double duty = atof(argv[2]);
    int period = atoi(argv[3]);

    motors(duty, period, direction);

    return 0;
}