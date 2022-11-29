/**
 * Spencer Lefever
 * COSC350 Lab 9 Task 3
 * 
 * Multiple Pipe across a fork/exec
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
    int file_pipes2[2];
    const char some_data[] = "Hi there, Kiddo";
    char buffer[BUFSIZ + 1];
    char buffer2[BUFSIZ + 1];
    pid_t fork_result;
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(file_pipes) == 0 && pipe(file_pipes2) == 0) {
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if (fork_result == 0) {
            close(file_pipes[WRITE_END]);
            close(file_pipes2[READ_END]);
            sprintf(buffer, "%d", file_pipes[READ_END]);
            sprintf(buffer2, "%d", file_pipes2[WRITE_END]);
            (void)execl("twoPipesChild", "twoPipesChild", buffer, buffer2, (char *)0);
            exit(EXIT_FAILURE);
        }
        else {
            close(file_pipes[READ_END]);
            close(file_pipes2[WRITE_END]);
            data_processed = write(file_pipes[WRITE_END], some_data,
            strlen(some_data));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
            wait();

            //Read childs message and print output
            data_processed = read(file_pipes2[READ_END], buffer, BUFSIZ);
            printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
        }
    }
    exit(EXIT_SUCCESS);
}