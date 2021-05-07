#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>

typedef struct my_msgbuff {
    long mtype;
    int buff[2];
} msgbuff;

int main(void) {

    key_t key;
    key_t shmkey;
    int shmid;
    int msqid;
    msgbuff rcv;
    int rcvbuff[2];
    int check;
    int* attachArray;
    
    key = ftok(".", 'B');
    msqid = msgget(key, 0666);
    shmkey = ftok(".", 'B');
    shmid = shmget(shmkey, 3*sizeof(int), 0666 | IPC_CREAT);
    attachArray = (int*)shmat(shmid, NULL, 0);
    attachArray[0] = attachArray[1] = attachArray[2] = 0;

    while (true) {
        while (attachArray[2] != 0) {
            sleep(1);
        }
        if ((check = msgrcv(msqid, (msgbuff*)&rcv, sizeof(rcv), 0, 0)) == -1) {
            puts("Error receiving input/End of input");
            break;
        }
        // Now write to shared memory
        attachArray[0] = rcv.buff[0];
        attachArray[1] = rcv.buff[1];
        attachArray[2] = 1; // Data has been written
        puts("written");
    }

    return 0;
}
