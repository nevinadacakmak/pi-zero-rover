/*
### Phase 1: Motor control : WIP

Desc: Get motors working on the Pi. Validate GPIO and PWM (Pulse Width Modulation).

Deliverable: C program that drives one TT motor forward, backward, and stop, 
using PWM for speed control via the L298N driver.
*/

/*
my notes: what do i send to l298n?
-> 2 pins. IN1 IN2 ENA.
IN1	IN2	Result
HIGH LOW forward
LOW	HIGH back
LOW	LOW	stop

ENA-PWM

to use: 

libgpiod library
gpiod_chip_open, gpiod_chip_get_line, gpiod_line_set_value
need a fcn for pwd
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main(){






    return 0;
}