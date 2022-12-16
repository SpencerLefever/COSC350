/**
 * Spencer Lefever
 * COSC350 Lab10 Task 2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char **argv)
{
	key_t key;
	int shmid;
	struct Memory *shm;
	key = ftok(".",'x'); //get key value
	//Open existing shared memory
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit (1);
	}
	//a pointer is attach to shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1)
	{
		perror("shmat error\n");
		exit(1);
	}

	//read from the shared memory
	while (shm->gostop == GO)
	{
		int i,j;
		int size = sizeof(shm->data.numbers)/sizeof(shm->data.numbers[0]);
		for(i = 0; i < size; i++){
			while(shm->data.counter == 0){
				if(shm->gostop == STOP)
					break;
			}
			shm->data.counter--;
			shm->data.numbers[i] = 0;
			for(j = 0; j < size; j++){
				printf("%d ", shm->data.numbers[j]);
			}
			printf("\n");
			shm->status = TAKEN;
			sleep(1);
		}
	}
	shmdt((void*)shm); //detach
	return 0;
}
