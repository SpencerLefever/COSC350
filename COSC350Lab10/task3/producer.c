/**
 * Spencer Lefever 
 * COSC350 Lab10 Task 3
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}
void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}

int main(int argc, char**argv)
{
	int shmid;
	int semid;
	key_t key;
	struct Memory *shm;

	key=ftok(".", 'x'); //get key value
	if((shmid = shmget(key, sizeof(struct Memory), 0))<0) // Open shared memory
	{
		perror("shmget error \n");
		exit(1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0); //attach to shared memory
	if((long)shm == -1)
	{
		perror("shmat error \n");
		exit(1);
	}
	if((semid = semget(key, 3, 0)) == -1){
		perror("semget");
		exit(1);
	}
	int item, index;
	int size = sizeof(shm->numbers)/sizeof(shm->numbers[0]);
	//Run forever
	while(1){
		//Assign random value between 0 to 10 until array is full
		int i;
		//Size of the array
			
			item = (rand() % (10 -0 +1)) +0;
			printf("%d\n", semctl(semid, EMPTY, GETVAL));
			//Down empty
			down(semid, EMPTY);
			//Down mutex
			down (semid, MUTEX);
			//Get current FULL value
			index = semctl(semid, FULL, GETVAL);
			//Input item
			shm->numbers[index] = item;
			for(i = 0; i< size; i++){
				printf("%d ", shm->numbers[i]);
			}
			printf("\n");
			//Return mutex to use
			up(semid, MUTEX);
			//Raise up full
			up(semid, FULL);
			sleep(1);
	}
	shm->gostop = STOP;
	shmdt((void *) shm); //detach
	return 0;
}