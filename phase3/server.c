/*
Accept movement commands over a TCP socket. Translate commands to motor signals.

solution for direction change signaling:
2 threads: 
-tcp socket, starts pwm and listens
-and pwm thread

and to avoid race conditions, we will use mutexes

shared variable: direction, motor_running
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

//one fcn for the pwn thread

void pwn_thread(){
    //TODO
    
}

int server(){

    //build the socket, listen, update current_direction

    //calls motor_setup

    //TODO



    return 0;
}