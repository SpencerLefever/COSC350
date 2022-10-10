/**
 * Spencer Lefever
 * COSC350 lab3 task6
 * 
 * Task5 but using pread instead of lseek
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
 
#define PERMISSION (S_IRWXU | S_IRGRP | S_IWGRP)

int main() {
    int nread, nByte, fdIn, fdOut;
	char *buffer[1];
    char *buffer2[128];

    fdIn = STDIN_FILENO;

	fdOut = creat("foorev1", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP); 

    nByte = read(fdIn,buffer2,4096);
    int writecount=0;
    while(pread(fdIn, buffer, 1, nByte-1)==1){ 
        pwrite(fdOut, buffer, nByte, writecount); 
        nByte--;
        writecount++; 
    }

}