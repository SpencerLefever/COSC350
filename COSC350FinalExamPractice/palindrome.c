/**
 * Spencer Lefever
 * COSC350 Lab4 Task2
 *
 * Palindrome
 */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int palind(int, int);

int main(int argc, char **argv)
{

    // Function takes in file name as an argument
    int fd1, fd2;

    fd1 = open(argv[1], S_IRUSR);
    fd2 = open(argv[1], S_IRUSR);

    if (palind(fd1, fd2) == 1)
    {
        printf("Palindrome detected in file \"%s\"\n", argv[1]);
    }
    else
    {
        printf("Palindrome not detected in file \"%s\"\n", argv[1]);
    }
}

/**
 * Function takes in 2 file descriptors open to the same file
 * uses lseek to scan file
 *
 * @returns 1 if the file contains a palindrome
 * @returns 0 if file does not contain a palindrome
 *
 */

int palind(int fd1, int fd2)
{

    int fileSize = lseek(fd1, 0, SEEK_END);
    lseek(fd1, 0, SEEK_SET);

    char *buffer = malloc(1);
    char *buffer1 = malloc(fileSize);
    char *buffer2 = malloc(fileSize);

    if((fileSize-1)%2==0) {
        // Read file from front
        read(fd1, buffer1, fileSize/2);
    }
    else {
        read(fd1, buffer1, (fileSize/2)-1);
    }
    

    //Set offset to back of file with pread
    int offset = lseek(fd2, -2, SEEK_END);
    while(offset >= fileSize/2)
    {
        pread(fd2, buffer, 1, offset);
        buffer2 = strncat(buffer2, buffer, 1);
        offset--;
    }

    // Compare two strings
    if (strcmp(buffer1, buffer2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
