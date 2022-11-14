/**
 * Spencer Lefever
 * COSC350 Lab8 Task1
 * 
 * Concurrent Calculation
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 2


int input=0;
int sumNum = 0;
int factorialNum = 1;
void *sum(void *);
void *factorial();

int main(int argc, char** argv) {
    if(argc != 2 ){
    printf("ARGUMENT ERROR \n");
    exit(-1);
    }

  input = atoi(argv[1]);
  pthread_t threads[NUM_THREADS];

  int rc = pthread_create(&threads[0],NULL,sum,(void *)input);
  pthread_join(threads[0],NULL);

  rc = pthread_create(&threads[1],NULL,factorial,(void *)input);
  pthread_join(threads[0],NULL); 

  if(rc != 0){
    printf("ERROR\n");
  }
}

void *sum(void *n){
  int num = input;

  for(int i=1;i<=num;i++){
    sumNum += i;
  }

  printf("SUM: %d\n",sumNum);
  pthread_exit(NULL);
}

void *factorial(){
  int num = input;
  int fact=1;
  int i=1;

  for(i;i<=num;i++){
    fact = fact*i;
  }

  printf("FACTORIAL: %d\n",fact);
  pthread_exit(NULL);
}