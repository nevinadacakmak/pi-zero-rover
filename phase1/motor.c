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
#include <pthread.h>

//default
int current_direction = 2;
int running = 1;
double duty_cycle = 0.75;
int period_ms = 10;

struct gpiod_chip *chip;
struct gpiod_line *in1line;
struct gpiod_line *in2line;
struct gpiod_line *enaline;
struct gpiod_line *in3line;
struct gpiod_line *in4line;
struct gpiod_line *enbline;
struct gpiod_line *in5line;
struct gpiod_line *in6line;
struct gpiod_line *encline;
struct gpiod_line *in7line;
struct gpiod_line *in8line;
struct gpiod_line *endline;

//pwd function, libgpiod doesnt support pi's pwd pin so its handmade
void pwm_cycle(struct gpiod_line *enaline){

    //HIGH - usleep(period * duty_cycle)
    //LOW  - usleep(period * (1 - duty_cycle))

    gpiod_line_set_value(enaline, 1);
    usleep(period_ms * 1000 * duty_cycle);
    gpiod_line_set_value(enaline, 0);
    usleep(period_ms * 1000 * (1 - duty_cycle));

}

int motor_setup(){

    //open gpio pins "chip"
    chip=gpiod_chip_open("/dev/gpiochip0");

    //get the pin number
    in1line=gpiod_chip_get_line(chip, 17);  // which gpio? 17 for in1, 27 for in2, 18 for ena
    in2line=gpiod_chip_get_line(chip, 27);
    enaline=gpiod_chip_get_line(chip, 18);

    in3line=gpiod_chip_get_line(chip, 22);
    in4line=gpiod_chip_get_line(chip, 23);
    enbline=gpiod_chip_get_line(chip, 24);

    in5line=gpiod_chip_get_line(chip, 5);
    in6line=gpiod_chip_get_line(chip, 6);
    encline=gpiod_chip_get_line(chip, 13);

    in7line=gpiod_chip_get_line(chip, 19);
    in8line=gpiod_chip_get_line(chip, 26);
    endline=gpiod_chip_get_line(chip, 12);

    //configure the value "line"
    gpiod_line_request_output(in1line, "motor", 0);
    gpiod_line_request_output(in2line, "motor", 0);
    gpiod_line_request_output(enaline, "motor", 0);

    gpiod_line_request_output(in3line, "motor", 0);
    gpiod_line_request_output(in4line, "motor", 0);
    gpiod_line_request_output(enbline, "motor", 0);

    gpiod_line_request_output(in5line, "motor", 0);
    gpiod_line_request_output(in6line, "motor", 0);
    gpiod_line_request_output(encline, "motor", 0);

    gpiod_line_request_output(in7line, "motor", 0);
    gpiod_line_request_output(in8line, "motor", 0);
    gpiod_line_request_output(endline, "motor", 0);

    return 0;
}

void *motor_loop(void *arg) {
    while (running) {
        if (current_direction == 0) 
        {
            // backward: in1=0, in2=1
            gpiod_line_set_value(in1line, 0);
            gpiod_line_set_value(in2line, 1);
            gpiod_line_set_value(in3line, 0);
            gpiod_line_set_value(in4line, 1);
            gpiod_line_set_value(in5line, 0);
            gpiod_line_set_value(in6line, 1);
            gpiod_line_set_value(in7line, 0);
            gpiod_line_set_value(in8line, 1);
            // call pwm_cycle
            pwm_cycle(enaline);
            pwm_cycle(enbline);
            pwm_cycle(encline);
            pwm_cycle(endline);
        }
        else if (current_direction == 1) 
        {
            // forward
            gpiod_line_set_value(in1line, 1);
            gpiod_line_set_value(in2line, 0);
            gpiod_line_set_value(in3line, 1);
            gpiod_line_set_value(in4line, 0);
            gpiod_line_set_value(in5line, 1);
            gpiod_line_set_value(in6line, 0);
            gpiod_line_set_value(in7line, 1);
            gpiod_line_set_value(in8line, 0);
            // call pwm_cycle
            pwm_cycle(enaline);
            pwm_cycle(enbline);
            pwm_cycle(encline);
            pwm_cycle(endline);
        }
        else if (current_direction == 2) 
        {
            // stop
            gpiod_line_set_value(in1line, 0);
            gpiod_line_set_value(in2line, 0);
            gpiod_line_set_value(in3line, 0);
            gpiod_line_set_value(in4line, 0);
            gpiod_line_set_value(in5line, 0);
            gpiod_line_set_value(in6line, 0);
            gpiod_line_set_value(in7line, 0);
            gpiod_line_set_value(in8line, 0);
            gpiod_line_set_value(enaline, 0);
            gpiod_line_set_value(enbline, 0);
            gpiod_line_set_value(encline, 0);
            gpiod_line_set_value(endline, 0);
        } 
        else if (current_direction == 3) 
        {
            // left
            gpiod_line_set_value(in1line, 1);
            gpiod_line_set_value(in2line, 0);
            gpiod_line_set_value(in3line, 0);
            gpiod_line_set_value(in4line, 1);
            gpiod_line_set_value(in5line, 1);
            gpiod_line_set_value(in6line, 0);
            gpiod_line_set_value(in7line, 0);
            gpiod_line_set_value(in8line, 1);
            // call pwm_cycle
            pwm_cycle(enaline);
            pwm_cycle(enbline);
            pwm_cycle(encline);
            pwm_cycle(endline);
        } 
        else if (current_direction == 4) 
        {
            // right
            gpiod_line_set_value(in1line, 0);
            gpiod_line_set_value(in2line, 1);
            gpiod_line_set_value(in3line, 1);
            gpiod_line_set_value(in4line, 0);
            gpiod_line_set_value(in5line, 0);
            gpiod_line_set_value(in6line, 1);
            gpiod_line_set_value(in7line, 1);
            gpiod_line_set_value(in8line, 0);
            // call pwm_cycle
            pwm_cycle(enaline);
            pwm_cycle(enbline);
            pwm_cycle(encline);
            pwm_cycle(endline);
        } 
    }
    return NULL;
}

void motor_cleanup(){
    //cleanup
    gpiod_line_release(in1line);
    gpiod_line_release(in2line);
    gpiod_line_release(enaline);
    gpiod_line_release(in3line);
    gpiod_line_release(in4line);
    gpiod_line_release(enbline);
    gpiod_line_release(in5line);
    gpiod_line_release(in6line);
    gpiod_line_release(encline);
    gpiod_line_release(in7line);
    gpiod_line_release(in8line);
    gpiod_line_release(endline);
    gpiod_chip_close(chip);
}