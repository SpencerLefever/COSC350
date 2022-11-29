/**
 * Spencer Lefever
 * COSC350 Lab 9 Task 3
 * 
 * Multiple pipes across fork/exec
 */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int data_processed;
    char buffer[BUFSIZ + 1];
    int file_descriptor;
    int file_descriptor2;
    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_descriptor);
    sscanf(argv[2], "%d", &file_descriptor2);

    data_processed = read(file_descriptor, buffer, BUFSIZ);
    printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);

    char buf[] = "Hi, Mom";

    data_processed = write(file_descriptor2, buf, strlen(buf));
    printf("%d - wrote %d bytes: %s\n", getpid(), data_processed, buf);

    close(file_descriptor);
    close(file_descriptor2);
    exit(EXIT_SUCCESS);
}