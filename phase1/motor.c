/*
### Phase 1: Motor control : WIP

Desc: Get motors working on the Pi. Validate GPIO and PWM (Pulse Width Modulation).

Deliverable: C program that drives one TT motor forward, backward, and stop, 
using PWM for speed control via the L298N driver.
*/

/*
-> 3 pins. IN1 IN2 ENA.

IN1	IN2	Result
HIGH LOW forward
LOW	HIGH back
LOW	LOW	stop

ENA-PWM

to use: 

libgpiod library
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <gpiod.h>
int current_direction = 2;  // başlangıçta dur
int running = 1;

//pwd function, libgpiod doesnt support pi's pwd pin so its handmade
void pwm_cycle(double duty_cycle, int period_ms, struct gpiod_line *enaline){

    //HIGH - usleep(period * duty_cycle)
    //LOW  - usleep(period * (1 - duty_cycle))

    gpiod_line_set_value(enaline, 1);
    usleep(period_ms * 1000 * duty_cycle);
    gpiod_line_set_value(enaline, 0);
    usleep(period_ms * 1000 * (1 - duty_cycle));

}

int motor_setup(double duty_cycle, int period_ms, int direction, int motor_running){

    //direction is 1(forward) or 0 (backward) or 2(stop)

    struct gpiod_chip *chip;
    struct gpiod_line *in1line;
    struct gpiod_line *in2line;
    struct gpiod_line *enaline;

    //open gpio pins "chip"
    chip=gpiod_chip_open("/dev/gpiochip0");

    //get the pin number
    in1line=gpiod_chip_get_line(chip, 17);  // which gpio? 17 for in1, 27 for in2, 18 for ena
    enaline=gpiod_chip_get_line(chip, 18);
    in2line=gpiod_chip_get_line(chip, 27);

    //configure the value "line"
    gpiod_line_request_output(in1line, "motor", 0);
    gpiod_line_request_output(in2line, "motor", 0);
    gpiod_line_request_output(enaline, "motor", 0);

    //inputs
    if (direction == 2){
        gpiod_line_set_value(in1line, 0);  //high versus low
        gpiod_line_set_value(in2line, 0); 
        gpiod_line_set_value(enaline, 0); //ena

    }

    if (direction == 1){
        gpiod_line_set_value(in1line, 1);  //high versus low
        gpiod_line_set_value(in2line, 0); 
        //gpiod_line_set_value(enaline, 0); //ena
        //todo: loop
        while (1) {
            pwm_cycle(duty_cycle, period_ms, enaline);
        }

    }

    if (direction == 0){
        gpiod_line_set_value(in1line, 0);  //high versus low
        gpiod_line_set_value(in2line, 1); 
        //gpiod_line_set_value(enaline, 0); //ena
        //todo: loop, will use motor_running later, or SIGINT
        while (1) {
            pwm_cycle(duty_cycle, period_ms, enaline);
        }
    }


    //cleanup
    gpiod_line_release(in1line);
    gpiod_line_release(in2line);
    gpiod_line_release(enaline);
    gpiod_chip_close(chip);

    return 0;
}

int motor_loop(){}//TODO

int motor_cleanup(){}//TODO