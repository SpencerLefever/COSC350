/**
 * Spencer Lefever
 * COSC350 Lab4 Part2 Task 1
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define PERMISSIONS (S_IRUSR | S_IWUSR)

int main(int argc, char** argv) {
    int input, alpha, num, other, copy;

    char* buf = malloc(1);

    input = open(argv[1], PERMISSIONS);
    alpha = creat("alpha", PERMISSIONS);
    num = creat("num", PERMISSIONS);
    other = creat("other", PERMISSIONS);

    while(read(input, buf, 1) > 0) {
        if(*buf == '\n') {
            write(num, buf, 1);
            write(alpha, buf, 1);
            write(other, buf, 1);
        }
        else{
            //Case if buf is a number
            if(*buf >= 48 && *buf <= 57){
                //Write the buf into num
                write(num, buf, 1);
                //Write blank space into other files
                write(alpha, " ", 1);
                write(other, " ", 1);
            }
            //Else if buf is a character
            else if((*buf >= 65 && *buf <= 90) || (*buf >= 97 && *buf <= 122)) {
                //Write character into alpha file
                write(alpha, buf, 1);
                //Write blank spaces into other files
                write(num, " ", 1);
                write(other, " ", 1);

            }
            //Buf is neither number nor character
            else if (*buf != '\n'){
                //Write special character to other
                write(other, buf, 1);
                //Write blank spaces to the other files
                write(alpha, " ", 1);
                write(num, " ", 1);
            }
            else {
                write(alpha, " ", 1);
                write(num, " ", 1);
                write(other, " ", 1);
            }
        }
    }
    close(alpha);
    close(num);
    close(other);

    alpha = open("alpha", PERMISSIONS);
    num = open("num", PERMISSIONS);
    other = open("other", PERMISSIONS);

    copy = creat("copy", PERMISSIONS);

    int asciiSpace = 32;
    //Malloc buffers for each file
    char* numBuf = malloc(1);
    char* alphaBuf = malloc(1);
    char* otherBuf = malloc(1);
    

    //Make copy of the file from alpha, num and others
    //All files are same size so we can loop by reading from input

    //lseek to move file offsets to front
    int fsize = lseek(input, 0, SEEK_END);
    
    fsync(alpha);
    fsync(num);
    fsync(other);


    for(int i=0; i<fsize; i++) {
        read(alpha, alphaBuf, 1);
        read(num, numBuf, 1);
        read(other, otherBuf, 1);

        //If all files have whitespace character print whitespace
        if(*alphaBuf == asciiSpace && *numBuf == asciiSpace && *otherBuf == asciiSpace) {
            write(copy, otherBuf, 1);
        }
        else if(*alphaBuf == '\n' && *numBuf == '\n' && *otherBuf == '\n') {
            write(copy, "\n", 1);
        }
        else {
            //If alpha is not whitespace print
            if(*alphaBuf != asciiSpace) {
                write(copy, alphaBuf, 1);
            }
            //If num is not whitespace print
            if(*numBuf != asciiSpace) {
                write(copy, numBuf, 1);
            }
            //If other is not whitespace print
            if (*otherBuf != asciiSpace) {
                write(copy, otherBuf, 1);
            }
        }
    }
}