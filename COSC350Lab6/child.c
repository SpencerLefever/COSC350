/**
 * Spencer Lefever
 * COSC350 Lab6 Task 4
 *
 * Child process being called by the exec call in task 4
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringToInt(char*);

int main(int argc, char** argv) {
	char *message = argv[0];
	int n = stringToInt(argv[1]);

	if(argc != 3){
		printf("3 arguments must be passed in\n");
		exit(1);
	}


	for(; n > 0; n--) {
		printf("Child process pid: %d message: %s\n", getpid(), message);
		sleep(stringToInt(argv[2]));
	}
		
	exit(0);
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
