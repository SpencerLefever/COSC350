/**
 * Spencer Lefever 
 * COSC 350 lab3 task1
 * 
 * Copt content of a readable 
 * file to file (clone)
 * using standard input and output 
 * file descriptor and i/o redirection
 */

/**
 * File Descriptors
 * 
 * Used to direct i/o for 
 * input, output, and error 
 * 
 * 0: stdin
 * 1: stdout
 * 2: stderr
 * 
 */


#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int offset, fd, nread;

    offset = lseek(STDIN_FILENO, 0, SEEK_END);

    //exit of lseek returns -1
    if(offset == -1) exit(0);  

    //Initialize buffer
    char buffer[offset];

    //Read in from file
    nread = read(STDIN_FILENO, buffer, offset);
    
    //Create file
    fd = creat("clone", S_IRUSR | S_IWUSR);

    //Write to clone file
    write(fd, buffer, offset);

}

/** 
 * To Execute with i/o redirection
 * 
 * ./task1 < foo
 */