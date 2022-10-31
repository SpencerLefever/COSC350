/**
 * Spencer Lefever
 * COSC350 Lab7 Task5
 * 
 * sigprocmask
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(){
    sigset_t sigset, nullsigset;

    //Add SIGINT and SIGQUIT to set
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGQUIT);

    sigprocmask(SIG_BLOCK, &sigset, NULL); //mask using sigset
    printf("First Loop:\n");

    for(int i=1;i<=5;i++){
        printf("%d\n",i);
        sleep(1);
    }
    signal(SIGQUIT, SIG_IGN); //Ignore previous SIGQUIT signals
    signal(SIGINT, SIG_IGN); //Ignore previous SIGINT signals
    
    sigprocmask(SIG_SETMASK, &nullsigset, NULL);
    sigdelset(&sigset,SIGQUIT); //remove SIGQUIT from set 
    sigprocmask(SIG_BLOCK, &sigset, NULL); //block only SIGINT
    signal(SIGQUIT, SIG_DFL); //Set SIGQUIT to default
    
    printf("Second Loop:\n");
    for(int i=1;i<=5;i++){
        printf("%d\n",i);
        sleep(1);
    }

}