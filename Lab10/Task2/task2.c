/*
 * task2.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/22/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/types.h> // Types
#include<stdbool.h> // bool alias
#include<pthread.h> // pthread Library
#include<time.h> // time()
#include<unistd.h> // sleep()
#include<signal.h> // Signal Functions

// Handler for producer and consumer
void handler(int sig) {
    if (sig == SIGUSR1) {
        puts("Handled SIGUSR1");
    } else if (sig == SIGUSR2) {
        puts("Handled SIGUSR2");
    } else {
        // Do nothing
    }
}

// For algorithm 1
#define N 10

// Global count
int count = 0;
// Global buffer
int buffer[N];

void printBuffer() {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ", buffer[i]);
    }
    puts("");
}

// Producer algorithm
void* producer(void* arg) {
    int item;
    while (true) {
        item = rand() % 10 + 1;
        if (count == N) {
            puts("Telling the consumer to wake up!");
            // Sleep until woken up by the consumer
            signal(SIGUSR1, handler);
            pause();
        }
        buffer[count] = item;
        count += 1;
        if (count == 1) {
            printBuffer();
            // Wake up the consumer
            kill(getpid(), SIGUSR2);
        }
    }
    pthread_exit(0);
    return 0;
}

// Consumer algorithm
void* consumer(void* arg) {
    int item;
    while (true) {
        if (count == 0) {
            signal(SIGUSR2, handler);
            pause();
        }
        int temp = buffer[0];
        buffer[0] = 0;
        count -= 1;
        if (count == N - 1) {
            puts("Telling the producer to wake up!");
            printBuffer();
            // Wake up the producer
            kill(getpid(), SIGUSR1);
        }
        // temp will just be gotten rid of
    }
    pthread_exit(0);
    return 0;
}


/*
 * Write a complete C program to simulate producer consumer problem
 * w/o using semaphores. Just simulate previous algorithms with count
 * variables. Show the race condition problems.
 * **You need to create two threads to simulate: producer and consumer
 */
int main(void) {
    // Seed the random generator
    srand(time(NULL));
    // Threads
    pthread_t p, c;
    // Check int check;
    int check;

    // Create the producer thread
    if ((check = pthread_create(&p, NULL, producer, NULL)) == -1) {
        puts("*** Error creating the producer thread ***");
        return 1; // Returning because there was an error creating the first thread
    }
    // Create the consumer thread
    if ((check = pthread_create(&c, NULL, consumer, NULL)) == -1) {
        puts("*** Error creating the consumer thread ***");
        return 2; // Returning because there was an error creating the second thread
    }
    // Join even though the threads run infinitely
    if ((check = pthread_join(p, NULL)) == -1) {
        puts("*** Error joining on the producer thread ***");
        return 3; // Returning because there was an error joining on the producer thread
    }
    if ((check = pthread_join(c, NULL)) == -1) {
        puts("*** Error joining on the consumer thread ***");
        return 4; // Returning because there was an error joining on the consumer thread
    }

    pthread_exit(0);
    return 0;
}
