/*
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/22/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/sem.h> // Semaphore Stuff
#include<sys/types.h> // Types
#include<stdbool.h> // bool alias
#include<time.h> // time()
#include<pthread.h> // Thread library
#include<unistd.h> // sleep()

// Max buffer size
#define N 10

// Global buffer
int buffer[N];

// Helpful macros for indexing semaphores
#define MUTEX 0
#define FULL 1
#define EMPTY 2

// For the fourth argument of semctl
union semun {
    int val; // For SETVAL and GETVAL
    struct semid_ds *buf; // For IPC_STAT and IPC_SET
    unsigned short *array; // For GETALL and SETALL
};

/* 
 * up Function:
 * This function will increase a semaphore's value by 1
 * at the specified index
 */
void up(int semid, int index) {
    // Create the operation structure
    struct sembuf sb = {index, 1, 0};
    // Check int
    int check;
    // Execute the operation on the semaphore of a specified index
    if ((check = semop(semid, &sb, 1)) == -1) {
        puts("*** Error increasing the value of the semaphore ***");
        exit(10); // Exiting because there was an error increasing the value of the semaphore
    }
}

/* 
 * down Function:
 * This function will decrease a semaphore's value by 1
 * at the specified index
 */
void down(int semid, int index) {
    // Create the operation structure
    struct sembuf sb = {index, -1, 0};
    // Check int
    int check;
    // Execute the operation on the semaphore of a specified index
    if ((check = semop(semid, &sb, 1)) == -1) {
        puts("*** Error decreasing the value of the semaphore ***");
        exit(11); // Exiting because there was an error decreasing the value of the semaphore
    }
}

/*
 * printBuffer Function:
 * This function will print the buffer to the screen
 */
void printBuffer(int semid) {
    // Counter
    int i;
    // Check int
    int check;
    // Get the limit of the array
    if ((check = semctl(semid, FULL, GETVAL, NULL)) == -1) {
        puts("*** Error getting the value for FULL semaphore ***");
        exit(12); // Exiting because there was an error getting the value of FULL
    }
    if (check == 0) {
        puts("*empty buffer*");
    } else {
        // Print the buffer
        for (i = 0; i < check; i++) {
            printf("%d ", buffer[i]);
        }
        puts("");
    }
}

/*
 * producer Function:
 * This function will simulate the produder in the producer-consumer problem
 */
void* producer(void* arg) {
    // Convert semid
    long semid = (long)arg;
    // Check int
    int check;
    // Create the item
    int item;
    // Producer loop
    while (true) {
        //sleep(1);
        item = rand() % 10 + 1; // Produce item
        // Check while the buffer is full and sleep until it isn't any longer
        while ((check = semctl(semid, FULL, GETVAL, NULL)) == N) {
            puts("Producer waiting for consumer to take from buffer...");
            sleep(1);
        }
        // Insert an item
        while (true) { // Loop to wait for mutex to unlock
            // Check if the mutex is locked or not and loop on that
            if ((check = semctl(semid, MUTEX, GETVAL, NULL)) == 1) {
                down(semid, MUTEX); // Lock the mutex
                puts("Producer adding to the buffer...");
                if ((check = semctl(semid, FULL, GETVAL, NULL)) == -1) {
                    puts("*** Error getting value from full semaphore ***");
                    pthread_exit((void*)1);
                }
                buffer[check] = item; // Insert item into buffer at index FULL
                printf("Producer added %d to the buffer\n", buffer[check]);
                up(semid, FULL); // Add one value to the full semaphore
                down(semid, EMPTY); // Decrease one value from the empty semaphore
                printBuffer(semid);
                up(semid, MUTEX); // Unlock the data
                break; // Break out of this loop of waiting for mutex to unlock
            }
        }
    }

    pthread_exit(0);
    return 0;
}

/*
 * consumer Function:
 * This function will simulate the consumer in the producer-consumer problem
 */
void* consumer(void* arg) {
    // Convert semid
    long semid = (long)arg;
    // Check int
    int check;
    // Get the item
    int item;
    // Consumer loop
    while (true) {
        //sleep(1);
        // Check while the buffer is empty and sleep until it isn't
        while ((check = semctl(semid, FULL, GETVAL, NULL)) == 0) {
            puts("Consumer waiting for the producer to populate the buffer...");
            sleep(1);
        }
        // Removing and item will be simulated by the index of FULL being reduced
        // to where that item will no longer be printed
        while (true) { // Loop to wait for mutex to unlock
            // Check if the mutex is locked or not and loop on that
            if ((check = semctl(semid, MUTEX, GETVAL, NULL)) == 1) {
                down(semid, MUTEX); // Lock the mutex
                down(semid, FULL); // Decrease FULL => will now be the index of the "removed" item
                puts("Consumer taking from the buffer...");
                if ((check = semctl(semid, FULL, GETVAL, NULL)) == -1) {
                    puts("*** Error getting value from full semaphore ***");
                    pthread_exit((void*)1);
                }
                printf("Consumer got item %d from the buffer!\n", buffer[check]);
                up(semid, EMPTY); // Increase the size of EMPTY
                printBuffer(semid); // Print the buffer
                up(semid, MUTEX); // Unlock the mutex
                break; // Break out of this loop of waiting for mutex to unlock
            }
        }
    }

    pthread_exit(0);
    return 0;
}


/*
 * You need to create two threads: producer and consumer.
 * You need to use semaphores: two countable semaphores for empty and full
 * and one binary semaphore mutex for mutual exclusion in the algorithm.
 * You need to find out a way to demonstrate your program works properly.
 * You need to use ftok(), semget(), semctl(), and semop() system calls
 * for semaphores.
 */
int main(void) {
    // Seed the random generator
    srand(time(NULL));

    // Key value
    key_t key;
    // Sem id
    long semid; // Is a long value so no warning when passing to thread
    // Check int
    int check;
    // Thread ids
    pthread_t prod, cons;
    // Value set union
    union semun arg4;

    // Tokenize the file
    if ((key = ftok(".", 'K')) == -1) {
        puts("*** Error tokenizing the file ***");
        return 1; // Returning because there was an error tokenizing the file
    }

    // Get the semaphore id
    if ((semid = semget(key, 3, 0)) == -1) {
        puts("*** Error getting the semaphore (make sure it is created using buildsem.c) ***");
        return 2; // Returning because there was an error getting the semaphore
    }
    
    // Initialize the values of all of the semphores for the sake of this specific program
    arg4.val = 1;
    if ((check = semctl(semid, MUTEX, SETVAL, arg4)) == -1) {
        puts("*** Error setting value of the mutex semaphore ***");
        return 3; // Returning because there was an error setting the mutex value
    }
    arg4.val = 0;
    if ((check = semctl(semid, FULL, SETVAL, arg4)) == -1) {
        puts("*** Error setting the value of the full semaphore ***");
        return 4; // Returning because there was an error setting the full value
    }
    arg4.val = N;
    if ((check = semctl(semid, EMPTY, SETVAL, arg4)) == -1) {
        puts("*** Error setting the value of the empty semaphore ***");
        return 5; // Returning because there was an error setting the empty value
    }
    
    // Spawn the first thread
    if ((check = pthread_create(&prod, NULL, producer, (void*)semid)) == -1) {
        puts("*** Error spawning the first thread ***");
        return 6; // Returning because there was an error spawning the first thread
    }
    
    // Spawn the second thread
    if ((check = pthread_create(&cons, NULL, consumer, (void*)semid)) == -1) {
        puts("*** Error spawning the second thread ***");
        return 7; // Returning because there was an error spawning the second thread
    }

    // Join on each thread (even though they never end)
    if ((check = pthread_join(prod, NULL)) == -1) {
        puts("*** Error joining on the first thread ***");
        return 8; // Returning because there was an error joining on the first thread
    }
    if ((check = pthread_join(cons, NULL)) == -1) {
        puts("*** Error joining on the second thread ***");
        return 9; // Returning because there was an error joining on the second thread
    }

    pthread_exit(0);
    // All done!
    return 0;
}
