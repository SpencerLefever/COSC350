/**
 * Spencer Lefever
 * COSC350 Lab8 Task2
 * 
 * Wait for a thread for concurrent calculations
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 4

int scoreArray[20];

void sort();
void *minMax(void *num);
void *scores(void *num);
void *avg(void *num);


int main(){
    pthread_t t[NUM_THREADS];

    pthread_create(&t[0],NULL,scores,NULL);
    pthread_join(t[0],NULL);

    sort();
    
    pthread_create(&t[1],NULL,avg,NULL);
    pthread_create(&t[2],NULL,minMax,NULL);
    pthread_join(t[2],NULL);

}

void sort()
{
    for (int i = 0; i < 19; i++)
    {

        int min = i;
        for (int j = i+1; j < 20; j++){
          if (scoreArray[j] < scoreArray[min]){            
            min = j;
          }
        }

        int temp = scoreArray[min];
        scoreArray[min] = scoreArray[i];
        scoreArray[i] = temp;
    }
}


void *minMax(void *num){
  printf("Min: %d\n",scoreArray[0]);
  printf("Max: %d\n",scoreArray[19]);
}
void *scores(void *num){
  for(int i=0;i<20;i++){
    int num = 0;
    scanf("%d",&num);
    scoreArray[i] = num;
  }
}

void *avg(void *num){
  int sum = 0;
  for(int i=0;i<20;i++){
    sum += scoreArray[i];
  }
  double average = (double)sum/20;
  int median = scoreArray[9];
  printf("average: %f\n",average);
  printf("median: %d\n",median);
}