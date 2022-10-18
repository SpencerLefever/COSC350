/**
 * Spencer Lefever
 * COSC350 Lab6 Task 2
 *
 * Create a new process using fork
 *
 * Takes 4 command line arguments
 *
 * Nc: Number of iterations for child process
 * Np: Number of iterations for parent process
 * Tc: Sleep time for child process
 * Tp: Sleep time for parent process
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringToInt(char*);

int main(int argc, char** argv) {
	pid_t pid;
	char *message;
	int n;

	if(argc != 5){
		printf("4 arguments must be passed in\n");
		exit(1);
	}

	printf("fork program starting\n");
	pid = fork();

	switch(pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is the child";
			n = stringToInt(argv[1]);
			sleep(stringToInt(argv[3]));
		break;

		default:
			message = "This is the parent";
			n = stringToInt(argv[2]);
			sleep(stringToInt(argv[4]));
			break;
	}

	for(; n > 0; n--) {
		puts(message);
		sleep(1);
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
