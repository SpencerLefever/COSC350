/**
 * Spencer Lefever
 * COSC350 lab3 task3
 * 
 * Copy content of any file using
 * open file and 32 byte buffer
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PERMISSION (S_IRWXU | S_IRWXG)

int main() {
    int nread, fdOut;
    int bufferSize = 32;
    char* buffer = malloc(bufferSize);

    fdOut = creat("clone2", PERMISSION);

    while((nread = read(STDIN_FILENO, buffer, bufferSize)) > 0) {
        if(write(fdOut, buffer, bufferSize) != bufferSize) {
            printf("Write Error");
            exit(0);
        }
    }

    if(nread<0) {
        printf("Write Error");
        exit(0);
    }

    free(buffer);

}