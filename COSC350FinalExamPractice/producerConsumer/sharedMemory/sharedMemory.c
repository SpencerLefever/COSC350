#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>

#define FILLED 0
#define TAKEN 1
#define GO 3
#define STOP 4
#define NOTREADY -1

struct data {
    int data[5];
    int counter;
};

struct Memory {
    int status;
    int gostop;
    struct data data;
};

int main() {
    key_t key;
    int shmid;
    struct Memory* shm;

    int pid = fork();

    if(pid == 0) { 
        key = ftok(".", 'x');
        shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666);
        shm = shmat(shmid, NULL, 0);

        shm->status = NOTREADY;

        int size = sizeof(shm->data.data) / sizeof(shm->data.data[0]);
        while(1) {
            for(int i=0; i<size; i++) {
                shm->data.data[i] = rand() % 50;
                shm->data.counter++;

                if(shm->data.counter == size) {
                    shm->status = FILLED;
                }
            }
            while(shm->status != TAKEN);
            sleep(1);

        }
        shm->gostop = STOP;
        shmdt((void *) shm);
        shmctl(shmid, IPC_RMID, NULL);

    } else {
        sleep(1);
        key = ftok(".", 'x');
        shmid = shmget(key, sizeof(struct Memory), 0);
        shm = shmat(shmid, NULL, 0);
        int size = sizeof(shm->data.data) / sizeof(shm->data.data[0]);

        while(shm->gostop != STOP) {
            //Sum numbers taken from shared memory and output to stdout
            if(shm->status == FILLED) {
                int sum = 0;
                for(int i=0; i<size; i++) {
                    sum += shm->data.data[i];
                    shm->data.counter--;
                    printf("%d ", shm->data.data[i]);
                }
                printf("\nSum of shared memory numbers: %d\n", sum);
                sleep(1);
                if(shm->data.counter == 0) {
                    shm->status = TAKEN;
                }
            }
        }
        shmdt((void *) shm);
        
    }

    return 0;
}

