#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "motor.h"
#include "server.h"


int main(int argc, char *argv[]) {

    //where is the input coming from? terminal for now? for phase 1, yes
    //terminal for now: direction, duty_cycle, period_ms

    if (argc != 4) {
    printf("error, please input 3 numbers: direction (0,1), duty, period (in ms)");
    return 1;
    }

    int direction = atoi(argv[1]);
    double duty = atof(argv[2]);
    int period = atoi(argv[3]);

    motor_setup();

    pthread_t pwm_thread;
    pthread_create(&pwm_thread, NULL, motor_loop, NULL);
    
    server_start();
    
    running = 0;
    pthread_join(pwm_thread, NULL);
    motor_cleanup();

    return 0;
}