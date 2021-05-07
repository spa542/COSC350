#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<stdbool.h>
#include<unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

#define SEM1 0
#define SEM2 1

int main(void) {
    
    key_t key;
    int semid;
    union semun arg4;
    
    key = ftok(".", 'K');
    semid = semget(key, 2, 0666 | IPC_CREAT);
    arg4.val = 1;
    semctl(semid, SEM1, SETVAL, arg4);
    semctl(semid, SEM2, SETVAL, arg4);
}
