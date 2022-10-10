/**
 * Spencer Lefever
 * COSC350 lab3 task5
 * 
 * Open file as input and write
 * into file using lseek (foorev) as reverse order
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PERMISSION (S_IRWXU | S_IRGRP | S_IWGRP)

int main() {
    int nread, fdIn, fdOut;
    char* buffer = malloc(1);

    fdIn = STDIN_FILENO;

    fdOut = creat("foorev", PERMISSION);

    off_t offset = lseek(fdIn, -1, SEEK_END);
    
    while(read(fdIn, buffer, 1) == 1 && offset >= 0) {
        write(fdOut, buffer, 1);
        offset--;
        lseek(fdIn, offset, SEEK_SET);
    }

    free(buffer);
}