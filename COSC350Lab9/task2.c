/**
 * Spencer Lefever
 * COSC350 Lab 9 Task 2
 * 
 * Pipe across a fork/exec
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define READ_END 0
#define WRITE_END 1


int main() {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if (fork_result == 0) {
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe4", "pipe4", buffer, file_pipes[WRITE_END], (char *)0);
            exit(EXIT_FAILURE);
        }
        else {
            data_processed = write(file_pipes[1], some_data,
            strlen(some_data));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
            close(file_pipes[WRITE_END]);
            wait();
        }
    }
    exit(EXIT_SUCCESS);
}