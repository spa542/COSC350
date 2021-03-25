/*
 * task2.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<signal.h> // signal()
#include<unistd.h> // sleep()

/*
 * ouch Function:
 * Signal handler that prints out the signal caught and
 * sends a signal back to the calling process
 */
void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    (void) signal(SIGINT, SIG_DFL);
}

/*
 * ctrlc1.c
 */
int main(void) {
    (void) signal(SIGINT, ouch);
    while(1) {
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}
