/**
 * Spencer Lefever
 * 
 * COSC350 Practice Exam task3
 * 
 * Child and parent communication through a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1


void sig_handler(int signo) {
    puts("SIGUSR1 SENT");
}

int main() {
    int fd;
    int pipefds[2];

    signal(SIGUSR1, sig_handler);

    pipe(pipefds);

    int pid = fork();

    if(pid == 0) { //Child
        fd = creat("task3.txt", 0666);
        //Write to file
        write(fd, "Hi, Mom", 8);

        //Send SIGUSR1
        kill(getppid(), SIGUSR1);

        //Receive message from pipe and print to stdout
        close(pipefds[WRITE]);

        char line[256];
        read(pipefds[READ], line, 256);

        printf("My mom said %s\n", line);
    } else { //Parent
        //Wait for message from child
        pause();

        fd = open("task3.txt", 0666);

        char* buf = malloc(8);
        //Grab message from file and print to stdout
        read(fd, buf, 8);

        printf("My son said %s\n", buf);

        //Send message "What do you want through a pipe"
        close(pipefds[READ]);

        write(pipefds[WRITE], "what do you want", 17);
    }
}