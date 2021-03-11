/*
 * child.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/11/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/types.h> // pid_t
#include<unistd.h> // getpid()
#include<string.h> // String functions

/*
 * This program will be executed by a child process that is spawned 
 * from forkExec.c
 */
int main(int argc, char** argv) {

    // Check to make sure # of arguments is correct
    if (argc != 4) {
        puts("*** Invalid # of args ***");
        exit(1); // Returning because the # of arguments is incorrect
    }

    // Copy over the message
    char message[strlen(argv[1])];
    strcpy(message, argv[1]);
    // Get the other integer variables
    int Nc = atoi(argv[2]), Tc = atoi(argv[3]);
    
    for (; Nc > 0; Nc--) {
        printf("Child PID: %d Message: %s\n", getpid(), message);
        sleep(Tc);
    }

    exit(37); // Success!
}
