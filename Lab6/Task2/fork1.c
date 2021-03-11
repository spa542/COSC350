/*
 * task2.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/11/21
 */
#include<sys/types.h> // pid_t
#include<unistd.h> // fork(), sleep()
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library

/*
 * Modify the fork1.c to take four command line args:
 * Nc - number o fiterations for child process
 * Np - number of iterations for parent process
 * Tc - sleep time for child process
 * Tp - sleep time for parent process
 * Run teh program as fork1 5 3 1 1 => Should be the same as the original
 * version
 * Run the program with teh following values
 * 5 3 1 5
 * 5 3 5 1
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
    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child";
            n = Nc;
            break;
        default:
            message = "This is the parent";
            n = Np;
            break;
    }
    for(; n > 0; n--) {
        puts(message);
        if (pid == 0) {
            sleep(Tc);
        } else {
            sleep(Tp);
        }
    }

    exit(0); // Done!
}
