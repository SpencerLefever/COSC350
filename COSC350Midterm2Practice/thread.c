/**
 * Spencer Lefever
 * COSC350 Midterm 2
 * 
 * Wait for a thread for a concurrent calculation
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *getScores(void *);
void *getMinMax(void *);
void *getMidAvg(void *);
void *clearBuf(void *);

const int NUM_THREADS = 4;
int scores[20];

int main() {

    pthread_t threads[NUM_THREADS];
    int rc;
    void *tmp1, *tmp2, *tmp3, *tmp4;

    //Create the threads
    rc = pthread_create(&threads[0], NULL, getScores, NULL);
    pthread_join(threads[0], &tmp1);

    rc = pthread_create(&threads[1], NULL, getMidAvg, NULL);
    rc = pthread_create(&threads[2], NULL, getMinMax, NULL);

    pthread_join(threads[1], &tmp2);
    pthread_join(threads[2], &tmp3);

    rc = pthread_create(&threads[3], NULL, clearBuf, NULL);
    pthread_join(threads[3], &tmp4);   

}

void *getScores(void* v) {
    for(int i=0; i<20; i++) {
        scores[i] = rand()%100;
        printf("%d ", scores[i]);
    }
}

void *getMinMax(void* v) {
    int min = 100;
    int max = 0;

    for(int i=0; i<20; i++){
        if(scores[i] > max) {
            max = scores[i];
        }
        if(scores[i] < min) {
            min = scores[i];
        }
    }
    printf("Min: %d\n", min);
    printf("Max: %d\n", max);
}

void *getMidAvg(void* v) {
    double avg;
    int sum = 0;
    
    for(int i=0; i<20; i++) {
        sum+=scores[i];
    }

    avg = ((double)sum)/20;

    printf("Avg: %f\n", avg);
    printf("Mid: %d\n", scores[9]);
}

void *clearBuf(void* v) {
    //Clear arr
    for(int i=0; i<20; i++) {
        scores[i] = 0;
    }
    //Print updated arr
    for(int i=0; i<20; i++) {
        printf("%d ", scores[i]);
    }
}