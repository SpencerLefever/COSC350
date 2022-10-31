/**
 * Spencer Lefever
 * COSC350 Lab7 Task4
 * 
 * Using signal and kill system calls
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
void sig(int);

int main(){
    printf("\n");
    int pid = fork();
    if(pid == 0){ //first child
        kill(getppid(), SIGUSR1); //send SIGUSR1 to parent
    }
    else if(pid > 0){
        int pid2 = fork(); //make second child from parent
        if(pid2 > 0){ //parent
            signal(SIGUSR1, sig); //If SIGUSR1 or SIGUSR2 is found, send to sig()
            signal(SIGUSR2, sig);
            int s;
            pid = wait(&s); //Wait for child to finish
        }
        else if(pid2 == 0){//second child
            kill(getppid(), SIGUSR2); //send SIGUSR2 to parent
        }
        
    }
}

void sig(int signo){
    if(signo == SIGUSR1){
        printf("Hi Honey! Anything wrong?\n");
    }else if(signo == SIGUSR2){
        printf("Do you make trouble again?\n");
    }
}