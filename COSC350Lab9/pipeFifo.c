/**
 * Spencer Lefever
 * COSC350 Lab 9 Task 4
 * 
 * FIFOs
 * 
 * The mkfifo system call is used to make a fifo
 * mkfifo /tmp/task4_fifo
 * mkfifo(/tmp/task4_fifo, O_NONBLOCK)
 * 
 * Another way to open a fifo would be to use the open system call
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define READ_END 0
#define WRITE_END 1
#define BUFFERSIZE 20
#define PATH "/tmp/task4_fifo"

int main() {
    int data_processed, retval;
    int file_pipes[2];
    int pid;
    char line[BUFFERSIZE];
    const char* some_data = "123";
    //char buffer[BUFSIZ + 1];
    char* buffer = malloc(strlen(some_data));

    //memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, some_data);
    
    if(retval == -1) {
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if(pid==0) {
        file_pipes[WRITE_END] = open(PATH, O_WRONLY);
        data_processed = write(file_pipes[WRITE_END], buffer, strlen(buffer));
        printf("Wrote %d bytes\n", data_processed);
    } else {
        file_pipes[READ_END] = open(PATH, O_RDONLY);

        data_processed = read(file_pipes[READ_END], line, BUFFERSIZE);
        line[data_processed] = '\0';

        printf("Read %d bytes: %s\n", data_processed, line);
    }

    

}
