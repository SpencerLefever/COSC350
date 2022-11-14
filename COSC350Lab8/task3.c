/**
 * Spencer Lefever
 * COSC350 Lab8 Task3
 * 
 * Interprocess communication using pipe
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int mypipe[2];

int main(int argc, char *argv[]){
    pipe(mypipe);
    if(argc != 3){
        printf("ERROR\n");
        exit(-1);
    }
    
    char *num1 = argv[1];
    char *num2 = argv[2];
    char buf[3];
    strncat(buf,num1,1);
    strncat(buf,num2,1);
    
  
  
    int pid = fork();
    if(pid == 0){
        char buf2[128];
        close(mypipe[1]);
        read(mypipe[0],buf2,10);
        
        char c1 = buf2[0];
        int num12 = c1 - '0';
        char c2 = buf2[1];
        int num22 = c2 - '0';
        
        if((c1 < 48 || c1 > 57) && (c2 < 48 || c2 > 57)){
            printf("NOT A NUMBER\n");
            exit(-1);
        }

        printf("SUM: %d\n",num12+num22);

    }else if(pid > 0){
        close(mypipe[0]);
        write(mypipe[1],buf,3);
        int s;
        wait(&s);
    }
}