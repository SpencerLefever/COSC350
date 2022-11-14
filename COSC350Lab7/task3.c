/**
 * Spencer Lefever
 * COSC350 Lab7 Task3
 * 
 * Process communication without sending a signal
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


int main(){
    int pid = fork();
    int fd = open("foo",O_CREAT|O_RDWR,0755); //opens 'foo'

    if(pid == 0){ //child
        write(fd,"Hi, Mom",7); //writes 'Hi Mom' to foo
        close(fd);
    }
    else if(pid > 0){ //parent
        int s;
        pid = wait(&s); //waits for child to be done
        char buffer[18] = "My son said "; //makes a buffer
        char filebuf[7];
        read(fd,filebuf,7); //reads message from 'foo'
        strncat(buffer,filebuf,7); //concatenates message from foo onto buffer
        printf("%s\n",buffer); 
        close(fd);
    }

}
