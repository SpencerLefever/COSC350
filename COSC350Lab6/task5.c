/**
 * Spencer Lefever
 * COSC350 Lab6 Task5
 * 
 * File sharing between child and parent
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define PERMISSIONS (S_IRUSR | S_IWUSR)

static int alarm_fired = 0;

void ding() {
    alarm_fired = 1;
}

int main(int argc, char** argv) {
    int fdIn, fdNum, fdChar;

    char* buf = malloc(1);
    pid_t pid;

    umask(0);

    fdIn = open(argv[1], O_RDONLY);
    fdNum = open("parent.txt", O_RDWR | O_CREAT, PERMISSIONS);
    fdChar = open("child.txt", O_RDWR | O_CREAT, PERMISSIONS);

    pid = fork();

    int tmp;

    if(pid==0) {
        while(read(fdIn, buf, 1) > 0) {
            if(*buf >= 48 && *buf <= 57){
                write(fdNum, buf, 1);
            }
        }

        lseek(fdIn, 0, SEEK_SET);

        kill(getppid(), SIGALRM);
    } else {
        signal(SIGALRM, ding);
        pause();

        while(read(fdIn, buf, 1) > 0) {
            if((*buf >= 65 && *buf <= 90) || (*buf >= 97 && *buf <= 122)) {
                write(fdChar, buf, 1);
            }
        }

    }

}