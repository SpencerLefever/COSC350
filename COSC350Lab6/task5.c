/**
 * Spencer Lefever
 * COSC350 Lab6 Task5
 * 
 * File sharing between child and parent
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    pid_t pid;
    int n;

    int fd = open(argv[1], S_IRWXU);


    printf("fork program starting\n");
	pid = fork();

	if(pid==-1){
        printf("Fork failed\n");
        exit(-1);
    }


    char* buf;
    while(read(fd, buf, 1) > 0) {
        
    }
	

}