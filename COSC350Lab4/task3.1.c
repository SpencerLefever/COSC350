/**
 * Spencer Lefever
 * COSC350 Lab4 Task3
 * 
 * Build a directory structure according to lab sheet 
 * using system calls
 * 
 * Using system calls copy hello file under ~/Dir2/Dir21
 * 
 * Using system calls make a symbolic link name toDir21 to Dir21
 * 
 * Using system calls, make a symbolic link name toHello to
 * the executable file ~/Dir21/hello
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    //Make directories with system calls
    int dir1 = mkdir("./Dir1", S_IRWXU);
    int dir2 = mkdir("./Dir2", S_IRWXU);
    int dir21 = mkdir("./Dir2/Dir21", S_IRWXU);

    char* buf = malloc(1);

    //File descriptors to open hello in working directory
    //and create hello exe in new directory
    int fd1 = open("hello", S_IRUSR);
    int fd2 = creat("Dir2/Dir21/hello", S_IRWXU);

    while(read(fd1, buf, 1) > 0) {
        write(fd2, buf, 1);
    }

    int symLink = symlink("../Dir2/Dir21", "./Dir1/toDir21");

 struct stat buff;
    lstat("Dir1/toHello",&buff);
    char *ptr;
    if(S_ISLNK(buff.st_mode)){
        ptr="Symbolic Link!";
    }
    printf("%s\n", ptr);
}