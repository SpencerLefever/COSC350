/**
 * Spencer Lefever
 * COSC350 Midterm 2 Practice
 * 
 * Making a pipe with popen write to cat command
 */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    FILE *pipeWrite, *pipeRead; 

    pipeWrite = popen("./add", "w");
    pipeRead = popen("./add", "r");

    if(pipeWrite != NULL) {
        
        fwrite("1", sizeof(char), 1, pipeWrite);
        fwrite("5", sizeof(char), 1, pipeWrite);
        pclose(pipeWrite);

        char c;
        int num;
        while((c = getchar()) != EOF) {
            printf("Checking pipe read\n");
            if(isdigit(c)) {
                num = atoi(&c);
                num += 1;
                // write(STDOUT_FILENO, "Num+1", 6);
                // write(STDOUT_FILENO, &num, 4);
                printf("Num+1 %d\n", num);
            }
        }
        printf("After checking pipe read\n");
        pclose(pipeRead);
        exit(0);
    }

    exit(1);

}