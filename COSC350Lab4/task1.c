/**
 * Spencer Lefever
 * COSC350 Lab4 Task1
 *
 * Reads command line input and parses
 * looking for embedded integers
 */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int stringToInt(char* );

int main(int argc, char** argv) {
    
    char* numString = malloc(1);
    char* stringBuffer = malloc(1);
    int fdIn, fdOut, digit, num;
    int digitCount = 1;
    char* buffer = malloc(1);
    
    
    //Exit if exactly 1 argument is not given
    if(argc != 2) {
        printf("Exactly 1 argument must be passed\n");
        exit(1);
    }

    //Open and read the input file and accumulate the digits into a string
    fdIn = open(argv[1], S_IRUSR);

    //Error if file is not found
    if(fdIn == -1) {
        printf("File not found\n");
        exit(2);
    }

    //Convert the string to an integer
    while(read(fdIn, buffer, 1) > 0) {
        //Check if current char is a digit
        if(!(*buffer < 48 || *buffer > 57)) {
            //Increment digit counter
            digitCount++;

            //Store current numString in buffer
            stringBuffer = numString;
            
            //realloc numString to allow for new digit
            numString = realloc(numString, digitCount);

            //Concatenate String
            numString = strncat(numString, buffer, 1);

            //realloc buffer to allow for new string next occurence
            stringBuffer = realloc(stringBuffer, digitCount);
        }
    }

    //Convert string to integer
    num = stringToInt(numString);
    free(numString);
    //Add 10 to the integer
    num += 10;

    //Convert sum back to string
    numString = malloc(digitCount);
    sprintf(numString, "%d", num);
    
    //System call to write string to stdout
    write(STDOUT_FILENO, numString, digitCount);
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
