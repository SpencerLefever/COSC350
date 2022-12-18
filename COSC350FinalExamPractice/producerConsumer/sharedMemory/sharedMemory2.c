#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>

#define NOTREADY -1
#define GO 0
#define STOP 1
#define FULL 3
#define TAKEN 4

struct Data {
    int counter;
    int data[5];
};

struct Memory {
    int status;
    int gostop;
    struct Data data;
};

int main() {
    key_t key;
    int shmid, size;
    struct Memory* shm;

    int pid = fork();
    if(pid == 0) { //Producer
        key = ftok(".", 'x');
        shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666);
        shm = shmat(shmid, NULL, 0);

        size = sizeof(shm->data.data) / sizeof(shm->data.data[0]);
        shm->data.counter = 0;
        shm->gostop = GO;
        while(1) {

            for(int i=0; i<size; i++) {
                shm->data.data[i] = rand() % 50;
                shm->data.counter++;
            }
            if(shm->data.counter == size) {
                shm->status = FULL;
            }
            while(shm->status != TAKEN);
            sleep(1);
        }
        shm->gostop = STOP;
        shmdt((void *) shm);
        shmctl(shmid, IPC_RMID, NULL);     


    } else { //Consumer
        key = ftok(".", 'x');
        shmid = shmget(key, sizeof(struct Memory), 0666);
        shm = shmat(shmid, NULL, 0);

        size = sizeof(shm->data.data) / sizeof(shm->data.data[0]);
        while(shm->gostop != STOP) {
            if(shm->status == FULL) {
                int sum = 0;
                for(int i=0; i<size; i++) {
                    sum += shm->data.data[i];
                    shm->data.counter--;
                    printf("%d ", shm->data.data[i]);
                }
                if(shm->data.counter == 0){
                    shm->status = TAKEN;
                }
                printf("\nSum of shm digits: %d\n", sum);
            }
            sleep(1);
        }
        shmdt((void *) shm);
    }

}