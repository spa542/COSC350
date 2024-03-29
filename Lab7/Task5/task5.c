/*
 * task5.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // sleep()
#include<signal.h> // sigprocmask()

/*
 * Write a C program that demonstrates how you can block and unblock signals.
 * You program will have two loops, each of which simply prints the integers from
 * 1 to 5 at 1 second intervals. During the first loop, SIGINT and SIGQUIT
 * are blocked. During the second loop, only SIGINT is blocked. While the 
 * program is running, you can try ^C and/or ^\ to see if they are blocked 
 * as expected. The signal SIGINT is usually bound to ^C by the terminal 
 * driver. The SIGINT signal terminates the program by default. The signal
 * SIGQUIT is usually bound to ^\ by the terminal driver. The signal SIGQUIT 
 * by default causes the program to terminate and creates a core file.
 */
int main(void) {
    
    // Create the counter
    int i;
    // Create the sigset
    sigset_t set1;
    sigset_t set2;
    // Initialize the sigset
    sigemptyset(&set1);
    // Add the first blocked signals to the set
    sigaddset(&set1, SIGQUIT);
    sigaddset(&set1, SIGINT);
    // Now set the mask
    sigprocmask(SIG_BLOCK, &set1, NULL);
    // First loop
    // This loop will block SIGINT and SIGQUIT
    for (i = 0; i < 5; i++) {
        printf("%d\n", i + 1);
        sleep(1);
    }
    // Initialize and add the removed signal to sigset
    sigemptyset(&set2);
    sigaddset(&set2, SIGQUIT);
    // Need to check if the there are pending SIGQUIT's in the queue, 
    // if so, then need to clear them
    sigset_t pending;
    sigpending(&pending);
    // If SIGQUIT is a member of the pending statuses then clear it so
    // not weird issue occurs
    if (sigismember(&pending, SIGQUIT)) {
        // Need to create a set for clearing the pending signals
        sigset_t clear_set;
        sigemptyset(&clear_set);
        sigaddset(&clear_set, SIGQUIT);
        int sig_num;
        // Need to clear the SIGQUIT pending signals that were blocked earlier
        sigwait(&clear_set, &sig_num);
    }
    // Now unblock the signal SIGQUIT (not saving the new mask)
    sigprocmask(SIG_UNBLOCK, &set2, NULL);
    // Second loop
    // This loop will block SIGINT
    for (i = 0; i < 5; i++) {
        printf("%d\n", i + 1);
        sleep(1);
    }

    // All done!
    return 0;
}
