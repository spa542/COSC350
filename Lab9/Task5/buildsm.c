/*
 * buildsm.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard I/O
#include<sys/shm.h> // shmget()
#include<sys/ipc.h> // ftok()
#include<fcntl.h> // creat()
#include<unistd.h> // close()

/*
 * Build a shared memory which will be used for inter-process communication
 * between two processes.
 */
int main(void) {

    key_t key;
    // Tokenize the file
    if ((key = ftok(".", 'B')) == -1) {
        puts("*** Error tokenizing the file ***");
        return 1; // Returning because the file couldn't be tokenized
    }


    int shmid;
    // Create the shared memory pool
    if ((shmid = shmget(key, 2*sizeof(int), IPC_CREAT | 0666)) == -1) {
        puts("*** Error creating the shared memory pool ***");
        return 2; // Returning because there was an error creating the shared memory pool
    }

    return 0;
}
