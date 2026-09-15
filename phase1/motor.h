#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <gpiod.h>
extern int current_direction;
extern int running;

void pwm_cycle(double duty_cycle, int period_ms, struct gpiod_line *enaline);

int motors(double duty_cycle, int period_ms, int direction, int motor_running);