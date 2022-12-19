/**
 * Spencer Lefever
 * COSC350 Practice Exam
 * 
 * Create message queue and receive data from command line until Ctrl-D
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/shm.h>

struct Message {
    long mtype;
    char msg[200];
};

int main() {
    key_t key;
    int msgQid;
    struct Message msgBuf;

    key = ftok(".", '!');
    msgQid = msgget(key, IPC_CREAT | 0666);

    while(gets(msgBuf.msg), !feof(stdin)) {
        msgsnd(msgQid, (struct Message *) &msgBuf, sizeof(msgBuf.msg), 0);
        printf("Message sent: %s\n", msgBuf.msg);
    }

    msgctl(msgQid, IPC_RMID, NULL);
}