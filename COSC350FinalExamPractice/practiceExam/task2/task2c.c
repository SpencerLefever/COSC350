/**
 * Spencer Lefever
 * COSC350 Practice Exam
 * 
 * Get two integers from shared memory and calculate sum
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define N 2
#define NOTREADY -1
#define GO 1
#define STOP 2
#define FILLED 3
#define EMPTY 4

struct Data {
    int counter;
    int data[N];
};

struct Memory {
    int status;
    int gostop;
    struct Data data;
};

int main() {
    key_t key;
    int shmid;
    struct Memory* shm;

    key = ftok(".", '?');
    if ((shmid = shmget(key, sizeof(struct Memory), 0)) == -1) {
        perror("shmget");
    }
    
    if((shm = shmat(shmid, NULL, 0)) == -1) {
        perror("shmat");
    }
    //sleep(1);
    while(shm->gostop != STOP) {
        if(shm->status == FILLED) {
            puts("Filled detected");
            int sum=0;
            for(int i=0; i<N; i++) {
                sum += shm->data.data[i];
                shm->data.counter--;
                printf("%d ", shm->data.data[i]);
            }
            if(shm->data.counter == 0){
                shm->status = EMPTY;
            }
            printf("Sum of number: %d\n", sum);
        }
    }
    shmdt(shm);
}