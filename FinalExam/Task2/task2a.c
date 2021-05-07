#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<stdbool.h>

#define BUFFER_SIZE 80

typedef struct my_msgbuff {
    long mtype;
    int buff[2];
} msgbuff;

int main(void) {
    key_t key;
    int msqid;
    int nbyte;
    char buffer[BUFFER_SIZE];
    int sendbuff[2];
    msgbuff send;
   
    key = ftok(".", 'B');

    msqid = msgget(key, 0666 | IPC_CREAT);

    while ((nbyte = read(0, buffer, BUFFER_SIZE)) > 0) {
        if (sscanf(buffer, "%d%d", &sendbuff[0], &sendbuff[1]) == 2) {
            send.mtype = 1;
            send.buff[0] = sendbuff[0];
            send.buff[1] = sendbuff[1];
            msgsnd(msqid, (msgbuff*)&send, sizeof(send), 0);
        } else {
            puts("Invalid inputs");
        }
    }
    // Make sure to destroy the message queue
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
