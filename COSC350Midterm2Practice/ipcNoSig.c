/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 * 
 * IPC without sending signals
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int pid, fdOut;

    pid = fork();

    if(pid == 0) {
        fdOut = open("foo", O_RDWR | O_CREAT, S_IRWXU);

        write(fdOut, "Hi Mom", 7);
    }
    else {
        int status, fsize;
        char* buf;

        wait(&status);

        fdOut = open("foo", O_RDONLY, S_IRUSR);

        fsize = lseek(fdOut, 0, SEEK_END);
        buf = malloc(fsize);
        lseek(fdOut, 0, SEEK_SET);
        read(fdOut, buf, fsize);
        printf("After read from child %s\n", buf);


        write(STDOUT_FILENO, "My Son Said ", 13);

        write(STDOUT_FILENO, buf, fsize);
        write(STDOUT_FILENO, "\n", 1);
        
    }
}