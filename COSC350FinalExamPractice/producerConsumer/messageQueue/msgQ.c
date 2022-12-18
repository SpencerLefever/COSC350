#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct MessageBuf {
    long mtype;
    char mtext[200];
};

int main() {
    key_t key;
    int msgQid;
    struct MessageBuf buf;

    int pid = fork();

    if(pid == 0){
        key = ftok(".", 'A');
        msgQid = msgget(key, 0644 | IPC_CREAT);

        while(gets(buf.mtext), !feof(stdin)) {
            msgsnd(msgQid, (struct MessageBuf *)&buf, sizeof(buf), 0);
            printf("Message sent: %s\n", buf.mtext);
            sleep(1);
        }
        printf("After while loop\n");
        msgctl(msgQid, IPC_RMID, NULL);
        sleep(1);
        kill(getppid(), SIGTERM);
        exit(0);

    } else {
        sleep(1);
        char msgBuf[200];
        int n;
        key = ftok(".", 'A');
        msgQid = msgget(key, 0644);
        printf("Ready to receive\n");     
        int ppid = getppid();
        while(ppid == getppid()) {
            msgrcv(msgQid, (struct MessageBuf *) &buf, sizeof(buf), 0, 0);
            if(sscanf(buf.mtext, "%s", msgBuf) == 1){
			    printf("Message received: %s\n", msgBuf);
            }
            sleep(1);
        }
        printf("After receiver while loop\n");
    }
}