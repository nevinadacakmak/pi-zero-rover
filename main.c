#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "motor.h"


int main(int argc, char *argv[]) {

    //where is the input coming from? terminal for now?
    //terminal for now: direction, duty_cycle, period_ms

    if (argc != ) {
    //error
    return 1;
    }

    int direction = atoi(argv[]);
    double duty = atof(argv[]);
    int period = atoi(argv[]);

    motors(duty, period, direction);

    return 0;
}