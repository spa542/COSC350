/*
 * task2.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/1/2021
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<pthread.h> // Thread library
#include<unistd.h> // read()
#include<string.h> // strtok()

#define ARRAY_SIZE 20

// Global integer array
int values[ARRAY_SIZE];

// Functions for each thread
void* getTestScores(void*); // Thread 1 will do this
void* calcAvgMed(void*); // Thread 2 will do this
void* calcMinMax(void*); // Thread 3 will do this
void* cleanUp(void*); // Thread 4 will do this

/*
 * Three threads are sharing an integer array (global) and each do different
 * jobs. Thread 1 will get up to 20 test scores from the keyboard and save
 * them into the array. Then, thread 2 will calculate an average score and
 * median value and display it while thread 3 will get the minimum and maximum
 * score and display it. Lastly, thread 4 will clear the buffer and set it to
 * 0 and display after thread 2 and 3 finished their job.
 */
int main(void) {

    // Error check
    int check;
    // Create buffer for input
    pthread_t th1, th2, th3, th4;

    // Create the first thread
    if ((check = pthread_create(&th1, NULL, getTestScores, NULL)) != 0) {
        puts("*** Error creating the first thread ***");
        return 1; // Returning because the first thread couldn't be created
    }

    pthread_exit(NULL);
    return 0;
}

/*
 * getTestScores Function:
 * This function will get up to 20 test scores from standard input 
 * and store them into the values array
 */
void* getTestScores(void* arg) {
    // Create the buffer
    char buff[80];
    // Error check
    int nbyte;

    printf("Enter test scores: (Max: 20)\n");
    if ((nbyte = read(0, buff, 80)) == -1 ) {
        puts("*** Error reading from standard input ***");
    }

    // Create the delimeter and the pointer that will move through the array
    char* move;
    char delim = ' ';
    // Tokenize the string 
    move = strtok(buff, &delim);

    // Number of integers in the array
    int numOfIntegers = 0;
    // Get the values
    int i, temp;
    values[0] = atoi(buff);
    for (i = 1; i < ARRAY_SIZE && move != NULL; i++) {
        if ((temp = atoi(move)) != 0) {
            values[i] = temp;
        }
        // Move the token 
        move = strtok(NULL, &delim);
    }

    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d\n", values[i]); 
    }
    

    pthread_exit(NULL);
    return NULL;
}

/*
 * calcAvgMed Function:
 * This function will wait for getTestScores to complete and then calculate 
 * the average and median scores out of the values in the array
 */
void* calcAvgMed(void* arg) {

    return NULL;
}

/*
 * calcMinMax Function:
 * THis function will wait for getTestScores to complete and then calculate 
 * the minimum and maximum scores out of the values in the array
 */
void* calcMinMax(void* arg) {

    return NULL;
}

/*
 * cleanUp Function:
 * This function will wait until all threads are complete to clean up the buffer
 * and print out the result
 */
void* cleanUp(void* arg) {
    
    return NULL;
}
