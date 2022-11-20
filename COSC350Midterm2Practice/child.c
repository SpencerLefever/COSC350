/**
 * Spencer Lefever
 * 
 * COSC350 Midterm 2 Review
 * 
 * Prints message n times and sleeps for m seconds child.c that gets execed
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int stringToInt(char* );

int main(int argc, char** argv) {

    int numRun, numSleep;

    numRun = stringToInt(argv[0]);
    numSleep = stringToInt(argv[1]);

    for(int i=0; i<numRun; i++) {
        printf("Hi from child\n");
        sleep(numSleep);
    }
    exit(45);
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