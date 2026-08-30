#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <gpiod.h>

void pwm_cycle(double duty_cycle, int period_ms, struct gpiod_line *enaline);

int motors(double duty_cycle, int period_ms, int direction);