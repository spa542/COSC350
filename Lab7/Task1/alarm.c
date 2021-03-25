/*
 * task1.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // fork()
#include<sys/types.h> // pid_t
#include<signal.h> // alarm(), sigaction()
#include<string.h> // memset()

static int alarm_fired = 0;

/*
 * ding Function:
 * The ding function will make alarm_fired true;
 */
void ding(int sig) {
    alarm_fired = 1;
}

/*
 * Copy alarm.c from BLP 4th edition pg 485 (468 in 3rd edition).
 * Modify alarm.c so it uses sigaction
 */
int main(void) {
    pid_t pid;
    printf("alarm application starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            /* Failure */
            perror("fork failed");
            exit(1);
        case 0:
            /* child */
            sleep(5);
            kill(getppid(), SIGALRM);
            exit(0);
    }
    /* if we get here we are the parent process */
    printf("waiting for alarm to go off\n");
    /* This is the old way
    (void) signal(SIGALRM, ding);
    */
    // Need to create and initialize the sigaction struct
    struct sigaction act;
    memset(&act, 0, sizeof(act)); // Initialize to default
    act.sa_handler = ding; // Assign the signal handler
    // This is the new way using sigaction
    sigaction(SIGALRM, &act, NULL);

    pause(); // Pause and wait for a a signal

    if (alarm_fired)
        printf("Ding!\n");

    printf("done\n");
    exit(0);
}
