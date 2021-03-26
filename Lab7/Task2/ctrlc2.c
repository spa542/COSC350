/*
 * task2.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // sleep()
#include<signal.h> // sigaction()

/*
 * ouch Function:
 * Signal handler that prints out the signal caught
 */
void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    signal(SIGKILL, SIG_DFL);
}

/*
 * ctrlc2.c
 */
int main(void) {
    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &act, 0);
    while(1) {
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}
