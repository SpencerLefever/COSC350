/**
 * Spencer Lefever
 * COSC350 lab3 task9
 * 
 * Decoding program to conver task 8 to original file
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define PERMISSION (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)\

int main(int argc, char** argv) {
    
    char* ascii = malloc(1);
    char* buffer = malloc(1);
    char* buffer2 = malloc(1);

    int fdIn = open(argv[1], S_IRUSR);
    int fdOut = creat(argv[2], PERMISSION);

    while(read(fdIn, buffer, 1) == 1) {
        *ascii = *buffer;
            printf("Value of %c: %c\n", *buffer, *ascii);

        write(fdOut, ascii, sizeof(int));
    }

}