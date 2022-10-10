/**
 * Spencer Lefever
 * COSC350 lab3 task 7
 * 
 * Receives sequence of integers on cml and prints sum
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int charToInt(char* );

int main(int argc, char** argv) {
    
    int sum=0;
    int num;

    if(argc == 1) {
        printf("Program requires command line arguments\n");
        return -1;
    }

    for(int i=1; i<argc; i++) {
        
        //Conversion function
        if(charToInt(argv[i]) == -1) {
            printf("Argument must be a number\n");
            return -1;
        }
        int num = charToInt(argv[i]);
        sum += num;

    }
    printf("Sum of command line arguments: %d\n", sum);
}

int charToInt(char* c){
    int num = 0;
    for(int i=0; i<strlen(c); i++) {
        if(c[i] < 48 || c[i] > 57) {
            return -1;
        }
        num = num*10 + (c[i]-48);
    }
    return num;
}