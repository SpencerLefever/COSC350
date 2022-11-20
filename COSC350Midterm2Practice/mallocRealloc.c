/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 *
 * Mini test 3 question 3
 *
 * 1. Take random integer n as argument and make random string of that size
 * 2. Ask user for random integer m and append new string to original string
 *
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {

	char* stringBuf;
	int stringSize;
	int newSize;

	stringSize = atoi(argv[1]);

	stringBuf = malloc(stringSize);

	for(int i=0; i<stringSize; i++) {
		stringBuf[i] =  (rand() % 26) + 97;
	}

	printf("%s\n", stringBuf);

	printf("Enter an Integer: ");

	scanf("%d", &newSize);

	stringBuf = realloc(stringBuf, newSize+stringSize);

	for(int i=stringSize; i<stringSize+newSize; i++) {
		stringBuf[i] = '.';
		//Random chars instead of '.'
	}

	printf("%s\n", stringBuf);

	return 0;
}
