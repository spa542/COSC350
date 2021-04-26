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

#define N 10

// Create the Semaphore type
typedef int semaphore;

// Create the semaphores
semaphore mutex = 1;
semaphore empty = N;
semaphore full = 0;

// Producer Function
void* producer(void* arg) {
    int item;

    while (true) {
        item = 1 + rand() % 10; // produce_item()

         

    }
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

    return 0;
}
