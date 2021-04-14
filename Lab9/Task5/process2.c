/*
 * process2.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // read()
#include<sys/ipc.h> // IPC
#include<sys/shm.h> // Shared memory
#include<sys/types.h> // key_t
#include<stdbool.h> // bool alias

/*
 * Get two integers from shared memory and calculate the sum of 
 * the two integers and display them to stdout. Process 2 will keep
 * running until process 1 stops sending data.
 */
int main(void) {

    // Key id
    key_t key;
    // Shared memory id
    int shmid;
    // Integers to add
    int add1, add2;
    // Attach array pointer
    int* attachArray;

    // Tokenize the shared memory pool
    if ((key = ftok(".", 'B')) == -1) {
        puts("*** Error tokenizing the shared memory pool ***");
        return 1; // Returning because there was an error tokenizing the memory pool
    }

    // Get the shared memory pool
    if((shmid = shmget(key, 2*sizeof(int), 0)) == -1) {
        puts("*** Error getting the memory pool ***");
        return 2; // Returning because there was an error getting the memory pool
    }

    // Attach the array to the memory pool
    if ((attachArray = shmat(shmid, NULL, 0)) == (int*)-1) {
        puts("*** Error attaching the array to the shared memory pool ***");
        return 3; // Returning because there was an error attaching the array to the shared memory pool
    }

    // Get the data from the shared memory pool
    /*
    while (true) {
        if (attachArray != NULL) {
            add1 = attachArray[0];
            add2 = attachArray[1];
            printf("%d + %d = %d\n", add1, add2, add1+add2);
        } else {
            sleep(1);
        }
    }
    */


    return 0;
}
