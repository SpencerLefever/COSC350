/**
 * Spencer Lefever
 * COSC350 lab 3 task8
 * 
 * Passes input and output file names as arguments
 * Open input file as read only out output file rw-rw-rw
 * Encodes each character to ascii code number and rights output to file
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define PERMISSION (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)\

int main(int argc, char** argv) {
    
    int ascii;
    char* buffer = malloc(1);
    char* buffer2 = malloc(1);

    int fdIn = open(argv[1], S_IRUSR);
    int fdOut = creat(argv[2], PERMISSION);

    while(read(fdIn, buffer, 1) == 1) {
        ascii = *buffer;

        *buffer2 = ascii + '0';
        
        write(fdOut, buffer2, sizeof(int));
    }

}