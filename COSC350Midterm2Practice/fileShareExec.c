/**
 * Spencer Lefever
 * COSC350 Midterm Practice 2
 * 
 * File sharing between child and parent with exec
 */

/**
 * arg1 Num child
 * arg2 Num parent
 * arg3 Time child
 * arg4 Time parent
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int stringToInt(char* );


int main(int argc, char** argv) {

    int numRun, numSleep, pid;

    pid = fork();

    if(pid==0) {
        if (execl("child", argv[1], argv[3], NULL) < 0) {
            printf("Exec error\n");
            exit(1);
        }
    }
    else {
        int status;
        numRun = stringToInt(argv[2]);
        numSleep = stringToInt(argv[4]);

        for(int i=0; i<numRun; i++) {
            printf("Hi from parent\n");
            sleep(numSleep);
        }

        wait(&status);
    }
}

int stringToInt(char* c){
    int num = 0;
    int digit;
    int numDigits = strlen(c);
    for(int i=0; i<numDigits; i++) {
        int power = 1;
        if(c[i] < 48 || c[i] > 57) {
            printf("Digit %c is not a number in step %d\n", c[i], i);
            return -1;
        }
        
        //Get int of digit
        digit = c[i] - 48;
        //Loop to get power of digit
        for(int j = 0; j<(numDigits-i-1); j++) power = power * 10;

        digit = digit * power;
        
        num += digit;
    }

    return num;
   
}