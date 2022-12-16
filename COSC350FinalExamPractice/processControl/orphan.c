/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 * 
 * Create and orphan process
 * 
 * Orphan process: Parent finished before the child
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    
    int pid;

    pid = fork();

    if(pid == 0) {
        while(1) {
            write(STDOUT_FILENO, "My parent is still alive\n", 25);
            if(getppid() == 1) {
                write(STDOUT_FILENO, "My parent died I have a new parent now\n", 41);
            }
            sleep(5);
        }
    } else {
        while(1) {
            write(STDOUT_FILENO, "Parent still running\n", 23);
            sleep(5);
        }
    }
}