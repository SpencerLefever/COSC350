/**
 * Spencer Lefever
 * COSC350 Lab8 Task4
 * 
 * Interprocess communication using popen() and pclose()
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){

  char command[128];
  strncat(command, argv[1], sizeof(argv[1]));
  strncat(command, " ", sizeof(" "));
  strncat(command, argv[2], sizeof(argv[2]));

  popen(command,"w");
  int s;
  wait(&s);
  printf("\n");

  return 0;
}