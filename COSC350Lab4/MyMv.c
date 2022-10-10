/**
 * Spencer Lefever
 * COSC350 Task4
 * 
 * Create a mv command using link and unlink system calls
 * Program receives two arguments for file name and path to new directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char** argv) {
  if (argc != 3){
        printf("ERROR: NEED TO PASS 2 ARGUMENTS\n");
        exit(-1);
    }

    char *file = argv[1];
    char *path = argv[2];
    
    struct stat buf;
    stat(path, &buf);
    if( S_ISDIR(buf.st_mode)){ //If a directory
        strcat(path,file);
        int i= link(file,path);
        if(i != 0){
            printf("ERROR: NOT LINKED\n");
            exit(-1);
        }else{
            printf("LINKED in %s\n",path);
        }
        //unlink(argv[1]);
    }
    else{ //If not a directory
        
        int i= link(file,path);
        if(i != 0){
            printf("ERROR: NOT LINKED\n");
            exit(-1);
        }else{
            printf("LINKED in %s\n", path);
        }
        //unlink(argv[1]);
    }
    exit(0);

}