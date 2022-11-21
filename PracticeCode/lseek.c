/**
 * Spencer Lefever 
 * COSC350 lseek practice
 * 
 * Code used to gain a better understanding 
 * of lseek and system calls in C
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PERMISSION (S_IRUSR | S_IWUSR)

int main(int argc, char** argv)
{
    int offset, fd, nread, fsize;

    fd = open(argv[1], PERMISSION);

    //Find size of file using lseek
    fsize = lseek(fd, SEEK_SET, SEEK_END);

    int userInput = atoi(argv[2]);
    printf("User input: %d\n", userInput);
    //Set offset to argv[2] bytes
    offset = lseek(fd, SEEK_SET, userInput);

    printf("File Size: %d\n", fsize);
    printf("Offset: %d\n", offset);

}

