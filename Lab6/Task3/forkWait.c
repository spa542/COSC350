/*
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/11/21
 */
#include<sys/types.h> // pid_t
#include<sys/wait.h> // wait()
#include<unistd.h> // fork()
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library

/*
 * Modify so that the parent process waits for the child to finish.
 * Use code from page 475, for the wait portion.
 * Print your modified forkWait.c to hand in.
 * Run your forkWait with 5 3 1 1
 * Briefly describe how your result differs from the original program in task 2
 */
int main(int argc, char** argv) {
    // Check to make sure arg # is correct
    if (argc != 5) {
        puts("*** Incorrect # of args ***");
        return 1; // Returning because the incorrect # of args was given
    }
    // Get the values for each parameter as integers
    int Nc = atoi(argv[1]), Np = atoi(argv[2]),
        Tc = atoi(argv[3]), Tp = atoi(argv[4]);
    pid_t pid;
    char *message;
    int n;
    int exit_code; // Added for task 3
    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = Nc;
            exit_code = 37;
            break;
        default:
            message = "This is the parent";
            n = Np;
            exit_code = 0;
            break;
    }
    if (pid != 0) {
        int stat_val;
        pid_t child_pid;
        child_pid = wait(&stat_val);
        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val))
            printf("child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally\n");
    }
    for(; n > 0; n--) {
        puts(message);
        if (pid == 0) {
            sleep(Tc);
        } else {
            sleep(Tp);
        }
    }

    exit(exit_code); // Done!
}
