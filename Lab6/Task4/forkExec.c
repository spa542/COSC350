/*
 * task4.c
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
 * Modify forkExec so the child process image is replacedc by the 
 * image of a program named child.c. Use an exec family function to do this.
 * Write child.c to do the same this as the child process did in task 3.
 * - The child should give it's pid each time it prints the message
 * - The parent should give it's pid each time it prints the message
 * - The child program should take three command-line arguments:
 *   the message, Nc, and Tc
 * - To get an interesting exit status from the child, have it return 37, rather
 *   than 0
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
        int stat_val; // For return status of child
        pid_t child_pid; // For child pid
        child_pid = wait(&stat_val); // Make parent wait until child is finished
        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val)) {
            printf("child exited with code %d\n", WEXITSTATUS(stat_val));
        } else {
            printf("Child terminated abnormally\n");
        }
    } else {
        // Child process will execute the child.c program 
        // and create it's own individual process from this
        // ***ALL arguments need to be character arrays
        if (execl("./child", "./child", message, argv[1], argv[3], (char*)0) == -1) {
            puts("*** execl did not call properly ***");
            exit(100); // Returning because exec did not work properly
        }
        // The (char*)0 is so we can null terminate the arguments in argv
        // This is needed so no weird string runoffs or corruptions occur
    }
    // Just for parent now since child is executing a different program
    for(; n > 0; n--) {
        printf("Parent PID: %d Message: %s\n", getpid(), message);
        sleep(Tp); // For parent
    }

    exit(exit_code); // Done!
}
