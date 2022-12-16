/** Spencer Lefever
 * COSC350 Midterm2 Practice
 * 
 * Calculate factorial with 2 threads
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *evenSum(void*);
void *oddSum(void*);

int main(int argc, char** argv) {
    int num = atoi(argv[1]);
    void *tmp1, *tmp2;
    int rc;

    pthread_t threads[2];

    pthread_create(&threads[0], NULL, evenSum, (void *) num);
    pthread_create(&threads[1], NULL, oddSum, (void *) num);

    pthread_join(threads[0], &tmp1);
    printf("Even sum from main %d\n", (int) tmp1);
    pthread_join(threads[1], &tmp2);
    printf("Odd sum from main %d\n", (int) tmp2);

}

void *evenSum(void* v) {
    int num = (int)v;
    int sum = 0;

    for(int i=0; i<num; i+=2) {
        sum+=i;
    }
    pthread_exit((void *) sum);
}

void *oddSum(void* v) {
    int num = (int)v;
    int sum = 0;

    for(int i=1; i<num; i+=2) {
        sum+=i;
    }
    printf("Odd sum %d\n", sum);
    pthread_exit((void*) sum);
}

