/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice Questions
 * 
 * Opening a pipe manually with file descriptors
 * Pipe from child process to parent process
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main() {
    int fd[2];

    int pid;
    char line[256];

    pipe(fd);

    pid = fork();

    if(pid == 0) { //Child
        //Close the read end
        close(fd[0]);

        write(fd[1], "Pipe from child", 16);

    } else { //Parents
        //Close write end
        close(fd[1]);        
        read(fd[0], line, 256);
        write(STDOUT_FILENO, line, 256);
         
    }
}