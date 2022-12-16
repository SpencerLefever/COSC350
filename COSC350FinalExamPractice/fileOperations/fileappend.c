/**
 * Spencer Lefever
 * COSC lab3 task4
 * 
 * Open 2 files and append to 
 * a file using lseek()
 * 
 * The files that need to be appended are passes in as arugments
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMISSION (S_IRWXU | S_IRGRP | S_IWGRP)

int main(int argc, char** argv) {
    int nread, fd1, fd2, fd12;
    int bufferSize = 100;
    char* buffer = malloc(bufferSize);

    fd1 = open(argv[1], S_IRUSR);
    fd2 = open(argv[2], S_IRUSR);

    fd12 = creat("foo12", PERMISSION);

    //Write contents of file 1 to new file
    while((nread = read(fd1, buffer, bufferSize)) > 0) {
        if(write(fd12, buffer, bufferSize) != bufferSize) {
            printf("Write Error");
            exit(0);
        }
    }

    //lseek to set the cursor to end of file
    lseek(fd12, 0, SEEK_END);

    //Write contents of file 2 to new file
    while((nread = read(fd2, buffer, bufferSize)) > 0) {
        if(write(fd12, buffer, bufferSize) != bufferSize) {
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