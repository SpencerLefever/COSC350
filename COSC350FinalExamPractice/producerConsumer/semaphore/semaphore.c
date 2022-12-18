#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#define NOTREADY -1
#define GO 1
#define STOP 2
#define TAKEN 3
#define FILLED 4
#define MUTEX 0
#define FULL 1
#define EMPTY 2


union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct Memory{
	int status;
	int gostop;
	int numbers[5];
};

void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}
void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}

int main() {
    key_t key;
    int shmid, semid;
    struct Memory* shm;

    int pid = fork();

    if(pid == 0) {
        key = ftok(".", 'x');
        shmid = shmget(key, sizeof(struct Memory *), IPC_CREAT | 0666);
        shm = shmat(shmid, NULL, 0);
        semid = semget(key, 3, 0);

        int size = sizeof(shm->numbers) / sizeof(shm->numbers[0]);
        while(1) {
            
            down(semid, EMPTY);
            down(semid, MUTEX);
            for(int i=0; i<size; i++) {
                shm->numbers[i] = rand() % 50;
            }
            up(semid, FULL);
            up(semid, MUTEX);
            
        }
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);


    }
    else {
        sleep(1);
        key = ftok(".", 'x');
        shmid = shmget(key, sizeof(struct Memory *), IPC_CREAT | 0666);
        shm = shmat(shmid, NULL, 0);
        semid = semget(key, 3, 0);

        int size = sizeof(shm->numbers) / sizeof(shm->numbers[0]);
        while(1) {
            down(semid, FULL);
            down(semid, MUTEX);

            semctl(semid, FULL, GETVAL);
            int sum = 0;
            for(int i = 0; i < size; i++){
			    printf("%d ", shm->numbers[i]);
                sum += shm->numbers[i];
		    }
            printf("\nSum of numbers: %d\n", sum);

            up(semid, MUTEX);
            up(semid, EMPTY);
            sleep(1);
        }
        shmdt((void *) shm);
    }

    

}