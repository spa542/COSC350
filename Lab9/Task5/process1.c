/*
 * process1.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/ipc.h> // IPC
#include<sys/shm.h> // shm Functions
#include<sys/types.h> // Types
#include<string.h> // String Functions
#include<stdbool.h> // bool alias
#include<unistd.h> // read()
#include<signal.h> // signal()

#define BUFFER_SIZE 80

/*
 * Process keeps sending two integer values to shared memory until
 * ctrl-d. Before sending data, make sure there are definitely two integers
 */
int main(void) {

    // Check byte
    int nbyte;
    // Read buffer
    char buffer[BUFFER_SIZE];
    // Integers to be written to the shared memory pool
    int tmp1, tmp2;
    // Pointer to attach to shared memory
    int* attachArray;
    // Key id
    key_t key;
    // Shared memory id
    int shmid;

    // Tokenize the shared memory
    if ((key = ftok(".", 'B')) == -1) {
        puts("*** Error tokenizing the shared memory ***");
        return 1; // Returning because there was an error tokenizing the shared memory
    }

    // Get the shared memory pool
    if ((shmid = shmget(key, 3*sizeof(int), 0)) == -1) {
        puts("*** Error getting the shared memory pool ***");
        return 2; // Returning because there was an error getting the shared memory pool
    }

    // Attach the pointer to the shared memory pool
    if ((attachArray = (int*)shmat(shmid, NULL, 0)) == (int*)-1) {
        puts("*** Error attaching the integer pointer to the shared memory pool ***");
        return 3; // Returning because there was an error attaching the pointer to the shared memory pool
    }

    // Initialize the shared memory for the reader process
    attachArray[0] = attachArray[1] = attachArray[2] = 0;

    // Get the data from standard input
    while ((nbyte = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        // process1 will wait until client reads data and writes -1 to the shared memory
        while (attachArray[2] != 0) { // While the information hasn't been read yet
            sleep(1);
        }
        if (sscanf(buffer, "%d%d", &tmp1, &tmp2) == 2) { // Success
            // Now write the data to shared memory 
            attachArray[0] = tmp1;
            attachArray[1] = tmp2;
            attachArray[2] = 1; // Information is written to the buffer from the write process
        } else { // Fail
            puts("*** Invalid Integers ***");
            continue;
        }
    }

    // Array automatically detaches when process ends. The process will receive a SIGSTOP
    // and then will kill this process, the array will be destroyed and detached.
    return 0;
}
