/**
 * Spencer Lefever
 * COSC350 Lab10 Task 2
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char**argv)
{
	int shmid;
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
	shm->gostop = GO;
	shm->status = NOT_READY;

	int size = sizeof(shm->data.numbers) / sizeof(shm->data.numbers[0]);
	shm->data.counter = 0;
	//Run forever
	while(1){
		//Assign random value between 0 to 10 until array is full
		int i,j;
		//Size of the array
		for(i = 0; i < size; i++){
			//Random number generation between 0 to 10;
			shm->data.numbers[i] = (rand() % (10 - 0 +1)) + 0;
			shm->data.counter++;
			if(shm->data.counter == size){
				shm->status = FILLED;
				while(shm->status != TAKEN);
			} 
			for(j = 0; j< size; j++){
				printf("%d ", shm->data.numbers[j]);
			}
			printf("\n");
			sleep(1);
		}
	}
	shm->gostop = STOP;
	shmdt((void *) shm); //detach
	return 0;
}
