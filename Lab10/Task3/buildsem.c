/*
 * buildsem.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/26/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/ipc.h> // IPC Stuff
#include<sys/sem.h> // Semaphore Stuff
#include<unistd.h> // System Calls

/*
 * This program will just build a 3 semaphores for a process
 * to use elsewhere
 */
int main(void) {
    // Key value
    key_t key;
    // Check value
    int check;
    // Sem id
    int semid;

    // Tokenize the semaphore
    if ((key = ftok(".", 'K')) == -1) {
        puts("*** Error tokenizing the semaphore ***");
        return 1; // Returning because there was an error tokenizing the file
    }

    // Create the semaphore
    if ((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1) {
        puts("*** Error creating the semaphore ***");
        return 2; // Returning because there was an error creating the semaphore
    }

    // All done!
    return 0;
}
