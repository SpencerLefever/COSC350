/**
 * Spencer Lefever
 * COSC350 Lab8 Task3
 * 
 * Interprocess communication using pipe
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int mypipe[2];
int charToInt(char* );

int main(int argc, char *argv[]){
    pipe(mypipe);
    if(argc != 3){
        printf("ERROR\n");
        exit(-1);
    }
    
    char *num1 = argv[1];
    char *num2 = argv[2];

    char buf[strlen(num1) + strlen(num2) + 1];
    strncat(buf,num1,strlen(num1));
    strncat(buf, " ", 1);
    strncat(buf,num2,strlen(num2));

    printf("OG buf %s sizes: %ld %ld\n", buf, strlen(num1), strlen(num2));
  
    int pid = fork();
    if(pid == 0){
        char buf2[128];
        close(mypipe[1]);
        read(mypipe[0],buf2,(strlen(num1)+strlen(num2)+1));
        printf("Buf2 %s\n", buf2);
        char* c1 = buf2;
        int num12 = charToInt(c1);
        char* c2 = buf2+strlen(num1);
        int num22 = charToInt(c2);

        printf("%s %s\n", c1, c2);
        
        if((*c1 < 48 || *c1 > 57) && (*c2 < 48 || *c2 > 57)){
            printf("NOT A NUMBER\n");
            exit(-1);
        }

        printf("SUM: %d\n%d %d\n",num12+num22, num12, num22);

    }else if(pid > 0){
        close(mypipe[0]);
        write(mypipe[1],buf,strlen(num1) + strlen(num2)+1);
        int s;
        wait(&s);
    }
}

int charToInt(char* c){
    int num = 0;
    for(int i=0; i<strlen(c); i++) {
        if(c[i] < 48 || c[i] > 57) {
            return -1;
        }
        num = num*10 + (c[i]-48);
    }
    return num;
}