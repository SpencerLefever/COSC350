/**
 * Spencer Lefever
 * COSC350 Lab4 Task2
 *
 * Palindrome without pread
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
    lseek(fd2, 0, SEEK_END);

    char *buffer = malloc(1);
    char *buffer1 = malloc(fileSize);
    char *buffer2 = malloc(fileSize);
    char *charBuf1 = malloc(1);
    char *charBuf2 = malloc(1);
    

    //Loop for half of the file size
    if((fileSize-1)%2==0) {
        for(int i=0; i<fileSize/2; i++) {
            //Compare characters byte by byte and return false if palindrome is not detected

            //Read from back
            lseek(fd2, -2, SEEK_CUR);
            read(fd2, charBuf1, 1); 
            printf("%c", *charBuf1);

            //Read from front
            lseek(fd1, 0, SEEK_CUR);
            read(fd1, charBuf2, 1);
            printf("%c", *charBuf2);

            if(*charBuf1 != *charBuf2) {
                return 0;
            }
        }
        return 1;
    }
    else {
        for(int i=0; i<(fileSize/2)-1; i++) {
            //Read from back
            lseek(fd2, -2, SEEK_CUR);
            read(fd2, charBuf1, 1); 
            printf("%c", *charBuf1);

            //Read from front
            lseek(fd1, 0, SEEK_CUR);
            read(fd1, charBuf2, 1);
            printf("%c", *charBuf2);

            if(*charBuf1 != *charBuf2) {
                return 0;
            }
        }
        return 1;
    }
}

