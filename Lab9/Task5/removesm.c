/*
 * removesm.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h>  // Standard Library
#include<sys/ipc.h> // IPC
#include<sys/shm.h> // shmctl()
#include<sys/types.h> // key_t

/*
 * Remove shared membory built by buildsm.c
 */
int main(void) {

    key_t key;
    // Tokenize the file
    if ((key = ftok(".", 'B')) == -1) {
        puts("*** Error tokenizing the file ***");
        return 1; // Returning because there was an error tokenizing the file
    }

    int shmid;
    // Get the shared memory
    if ((shmid = shmget(key, 2*sizeof(int), 0)) == -1) {
        puts("*** Error getting the shared memory segment ***");
        return 2; // Returning because there was an error getting the shared memory segment
    }

    // Remove the shared memory
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
