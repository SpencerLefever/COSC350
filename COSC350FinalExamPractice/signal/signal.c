/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 * 
 * 2 children processes send SIGUSR 1 and 2 parent
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sigNo) {
    if(sigNo == SIGUSR1) {
        printf("SIGUSR1 Received from child\n");
    }
    else if(sigNo == SIGUSR2) {
        printf("SIGUSR2 received from child\n");
    }
}

int main() {

    int pid1, pid2;
    
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);

    pid1 = fork();
    if(pid1 == 0) {
        sleep(1);

        kill(getppid(), SIGUSR1);
    }
    else {
        pid2 = fork();
        if(pid2 == 0){
            sleep(1); 

            kill(getppid(), SIGUSR2);
        } else {
            while(1) { }
        }

    }
}
