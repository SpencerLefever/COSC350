/**
 * Spencer Lefever
 * COSC350 Practice Exam
 * 
 * Receive message from message queue and validate input of two integers
 * 
 * Created shared memory and write the two integers to shared memory
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

struct Message {
    long mtype;
    char msg[200];
};

struct Data {
    int counter;
    int data[N];
};

struct Memory {
    int gostop;
    int status;
    struct Data data;
};


int main() {
    key_t shmKey, msgqKey;
    int shmid, msgQid;
    struct Message msgQ;
    struct Memory* shm;

    //Receive message from message Q
    msgqKey = ftok(".", '!');
    msgQid = msgget(msgqKey, 0666);

    shmKey = ftok(".", '?');
    shmid = shmget(shmKey, sizeof(struct Memory), IPC_CREAT | 0666);
    shm = shmat(shmid, NULL, 0);
    shm->data.counter = 0;
    shm->gostop = GO;
    shm->status = NOTREADY;

    int size = sizeof(shm->data.data) / sizeof(shm->data.data[0]);

    int n1, n2;
    while(1) {
        msgrcv(msgQid, &msgQ, sizeof(msgQ), 0, 0);
        if(sscanf(msgQ.msg, "%d %d", &n1, &n2) == 2) {
            printf("Message received: %d %d\n", n1, n2);
            //Fill shared memory and switch status to filled
            shm->data.data[0] = n1;
            shm->data.counter++;
            shm->data.data[1] = n2;
            shm->data.counter++;
            if(shm->data.counter == size) {
                shm->status = FILLED;
                puts("Shm Filled!");
            }
            //Wait until memory is emptied by other program
            while(shm->status != EMPTY);
            sleep(1);
        }
    }
    shm->gostop = STOP;
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);

}