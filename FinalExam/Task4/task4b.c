#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdbool.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig) {
    if (sig == SIGUSR1) {
        puts("My child sent signal to me, now I kill myself"); 
        exit(0);
    }
}

void up(int semid, int index) {
    struct sembuf sb = {index, 1, 0};
    semop(semid, &sb, 1);
}

void down(int semid, int index) {
    struct sembuf sb = {index, -1, 0};
    semop(semid, &sb, 1);
}

#define SEM1 0
#define SEM2 1

int main(void) {

    key_t key;
    int semid;
    int myID;
    int check1, check2;
    signal(SIGUSR1, handler);
    signal(SIGCHLD, handler);
    
    key = ftok(".", 'K');
    semid = semget(key, 2, 0);

    myID = fork();
    if (myID == 0) {
        int i = 0;
        pid_t originalID = getppid();
        pid_t myPid = getppid();
        while (true) {
            i++;
            if (i == 100) {
                kill(originalID, SIGUSR1);
            }
            myPid = getppid();
            if (myPid != originalID) {
                puts("My parent killed himself, now I die");
                semctl(semid, 2, IPC_RMID);
                _exit(0);
            }
            check1 = semctl(semid, SEM1, GETVAL, NULL);
            check2 = semctl(semid, SEM2, GETVAL, NULL);
            if (check1 == 0 && check2 == 0) {
                puts("child is in critical section");
                up(semid, SEM1);
                up(semid, SEM2);
            } else {
                down(semid, SEM1);
                down(semid, SEM2);
            }
        }
    } else {
        while (true) {
            check1 = semctl(semid, SEM1, GETVAL, NULL);
            check2 = semctl(semid, SEM2, GETVAL, NULL);
            if (check1 == 0 && check2 == 0) {
                puts("parent is in critical section");
                up(semid, SEM1);
                up(semid, SEM2);
            } else {
                down(semid, SEM1);
                down(semid, SEM2);
            }
        }
    }

    return 0;
}
