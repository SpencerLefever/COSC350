/**
 * Spencer Lefever
 * Midterm Review filessharing
 * 
 * File sharing between a child and parent process
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define PERMISSIONS (S_IRUSR)

int main(int argc, char** argv) {
    int fdIn, chOut, pOut, fsize;


    fdIn = open(argv[1], O_RDWR);

    fsize = lseek(fdIn, 0, SEEK_END);

    int pid = fork();

    if(pid == 0) { //Child
        chOut = open("child.txt", O_RDWR | O_CREAT, PERMISSIONS);
        char* buf = malloc(1);

        //Open other processes output file to check for size change
        for(int i=0; i<fsize; i++) {
            lseek(fdIn, i, SEEK_SET);

            read(fdIn, buf, 1);

            if(isalpha(*buf)) {
                write(chOut, buf, 1);
            }
        }
    }
    else { //parent
        pOut = open("parent.txt", O_RDWR | O_CREAT, PERMISSIONS);
        char* buf = malloc(1);
        for(int i=0; i<fsize; i++) {
            lseek(fdIn, i, SEEK_SET);

            read(fdIn, buf, 1);

            if(isdigit(*buf)) {
                write(pOut, buf, 1);
            }
        }
    }
}
