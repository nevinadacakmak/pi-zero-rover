#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <gpiod.h>
#include <pthread.h>
extern int current_direction;
extern int running;
extern double duty_cycle;
extern int period_ms;

void pwm_cycle(struct gpiod_line *enaline);

int motor_setup();
void *motor_loop(void *arg); //
void motor_cleanup();