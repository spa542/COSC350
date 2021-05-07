#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<stdbool.h>

int main(void) {

    key_t key;
    int shmid;
    int add1, add2;
    int* attachArray;

    key = ftok(".", 'B');
    shmid = shmget(key, 3*sizeof(int), 0);
    attachArray = (int*)shmat(shmid, NULL, 0);

    struct shmid_ds data;

    while (true) {
        if (attachArray[2] == 1) {
            add1 = attachArray[0];
            add2 = attachArray[1];
            printf("%d + %d = %d\n", add1, add2, add1+add2);
            attachArray[0] = attachArray[1] = attachArray[2] = 0;
        } else {
            sleep(1);
        }
        shmctl(shmid, IPC_STAT, &data);
        if (data.shm_nattch == 1) {
            // Time to end 
            break;
        }
    }
    // Make sure to destroy the shm
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
