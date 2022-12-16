/**
 * Spencer Lefever
 * COSC350 Lab 10 Task 1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//Struct for message queue
struct my_msgbuf{
	long mtype;
	char mtext[200];
};

int main(void)
{
	struct my_msgbuf buf;
	int msqid;
	key_t key;
	//Create key
	if((key = ftok("msgQsnd.c", 'B')) == -1) {
		perror("ftok error");
		exit(1);
	}

	//Create message queue
	if((msqid = msgget(key, 0644 | IPC_CREAT)) == -1){
		perror("msgget error");
		exit(1);
	}
	printf("Enter two integers:\n");
	buf.mtype =1;//Used in fifo????
	//Get values from the input
	while(gets(buf.mtext), !feof(stdin)){
		//Write buf to the queue
		if(msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1){
			perror("msgsnd error");
		}
	}
	//Remove the message queue
	if(msgctl(msqid, IPC_RMID, NULL) == -1){
		perror("msgctl error");
		exit(1);
	}	

}
