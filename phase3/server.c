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
#include <sys/socket.h>
#include <netinet/in.h>
#include "motor.h"

int server_start() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 1);
    
    int clientfd = accept(sockfd, NULL, NULL);
    
    char buf[1];
    while (running) {
        recv(clientfd, buf, 1, 0);
        if (buf[0] == '\n') continue;
        if (buf[0] == 'W') 
        {
            current_direction = 1;
        }
        if (buf[0] == 'S') 
        {
            current_direction = 0;
        }
        if (buf[0] == 'A') 
        {
            current_direction = 4;
        }
        if (buf[0] == 'D') 
        {
            current_direction = 3;
        }
        printf("received: %c, direction: %d\n", buf[0], current_direction);
    }

    return 0;
}