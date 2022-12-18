#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#define MUTEX 0
#define NOTREADY -1
#define TAKEN 1
#define FILLED 2
#define GO 3
#define STOP 4
#define FULL 1
#define EMPTY 2
#define N 5

union senum {
    int val;
    struct semid_ds * buf;
    unsigned short* array;
};

struct Memory {
    int status;
    int gostop;
    int data[N];
};

void up(int semid, int index) {
    struct sembuf buf = {index, 1, 0};
    semop(semid, &buf, 1);    
}

void down(int semid, int index) {
    struct sembuf buf = {index, -1, 0};
    semop(semid, &buf, 1);
}

int main() {
    key_t key;
    int shmid, semid, size;
    struct Memory* shm;
    struct sembuf buf;
    union senum arg;

    int pid = fork();

    if(pid ==0) { //Producer
        key = ftok(".", 'z');
        shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666);
        shm = shmat(shmid, NULL, 0);
        semid = semget(key, N, 0);
        size = sizeof(shm->data) / sizeof(shm->data[0]);

        while(1) {

            // while(semctl(semid, MUTEX, GETVAL) == 0)
            //     sleep(1);

            down(semid, EMPTY);
            down(semid, MUTEX);
            int item;
            for(int i=0; i<size; i++) {
                item = i;
                //shm->data[i] = rand() % 50;
                //arg.val = rand() % 50;
                arg.val = i;
                if( semctl(semid, i, GETVAL, arg) == -1) {
                    perror("semctl");
                    exit(1);
                }
            }
            up(semid, FULL);
            up(semid, MUTEX);
        }
        shmdt((void *) shm);
        semctl(semid, IPC_RMID, NULL);


    } else { //Consumer
        sleep(1);
        key = ftok(".", 'z');
        shmid = shmget(key, sizeof(struct Memory), 0666);
        shm = shmat(shmid, NULL, 0);
        semid = semget(key, N, 0);
        size = sizeof(shm->data) / sizeof(shm->data[0]);
        int semBuf[5];
        while(1) {
            
            down(semid, FULL);
            down(semid, MUTEX);

            int sum = 0;
            for(int i=0; i<size; i++) {
                int x = semctl(semid, i, GETVAL);
                printf("%d ", x);
                sum += x;
                // sum += arg.val;            
                // printf("%d ", shm->data[i]);
                // sum += shm->data[i];
            }
            printf("\nSum: %d\n", sum);
            up(semid, EMPTY);
            up(semid, MUTEX);
           
            sleep(1);
        }
        shmdt((void *) shm);

    }

}