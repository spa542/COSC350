/*
 * task4.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // fork()
#include<sys/types.h> // pid_d
#include<signal.h> // kill(), signal(), pause()

/*
 * handle1 Function:
 * This function handles the signals SIGUSR1 and SIGUSR2
 */
void handler(int sig) {
    if (sig == SIGUSR1) {
        puts("Hi Honey!");
        return;
    }
    if (sig == SIGUSR2) {
        puts("Do you make trouble again?");
        return;
    }
}

/*
 * Write a complete C program in which two children processes send a signal
 * to the parent. The first child sends the message SIGUSR1 to the parent and 
 * the parent process respondes by writing the message "Hi Honey! Anything wrong?".
 * The second child sends a message SIGUSR2 to the parent and the parent responds
 * by writing the message "Do you make trouble again?".
 */
int main(void) {

    // Create the id variables for each child
    pid_t myID1, myID2;

    myID1 = fork();
    if (myID1 == 0) {
        // Send a message to the parent
        kill(getppid(), SIGUSR1);
        _exit(0);
    }
    myID2 = fork();
    if (myID2 == 0) {
        kill(getppid(), SIGUSR2);
        _exit(0);
    }

    // Create a handler for the signals
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    // Pause and wait for the signals
    pause();

    // All done!
    return 0;
}
