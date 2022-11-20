/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 * 
 * Create a zombie process
 * 
 * Zombie process: Child process finished before parent
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    
    int pid;

    pid = fork();

    if(pid == 0) {
        exit(0);
    } else {
        sleep(100);
    }
}