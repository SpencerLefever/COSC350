/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 * 
 * Program to add to numbers used in pipe program
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char** argv) {
    int x = 0,y = 0;
    char c;

    while((c = getchar()) != EOF) {
        if(isdigit(c) && x == 0) {
            x = atoi(&c);
        }
        else if (isdigit(c) && y == 0) {
            y = atoi(&c);
        }

        if(x != 0 && y != 0) {
            char buf = (x+y)+'0';
            write(STDOUT_FILENO, &buf, 1);

            exit(0);
        }
    }
}