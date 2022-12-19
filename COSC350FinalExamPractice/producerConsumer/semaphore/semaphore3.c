#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#define MUTEX 0
#define EMPTY 1
#define FULL 2
#define N 5

union senum {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};

void up (int semid, int index) {
    struct sembuf buf = {index, 1, 0};
    semop(semid, &buf, 1);
}

void down (int semid, int index) {
    struct sembuf buf = {index, -1, 0};
    semop(semid, &buf, 1);
}

int main() {
    key_t key;
    int semid;
    struct sembuf buf;
    union senum arg;
}
