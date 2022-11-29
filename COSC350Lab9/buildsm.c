/**
 * Spencer Lefever
 * COSC350 Lab 9 Task 5
 * 
 * buildsm Builds the shared memory used for the IPC
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define PATH "/tmp/task5_fifo"
#define MSGFLG IPC_CREAT | IPC_EXCL


int main(int argc, char** argv) {
    msgget(5, MSGFLG);
}