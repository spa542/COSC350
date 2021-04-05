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
#include<string.h> // memset()

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
    // Thread returns;
    void *ret1, *ret2;

    // Create the first thread
    if ((check = pthread_create(&th1, NULL, getTestScores, NULL)) != 0) {
        puts("*** Error creating the first thread ***");
        return 1; // Returning because the first thread couldn't be created
    }
    // Waiting for the first thread to finish
    if ((check = pthread_join(th1, &ret1)) != 0) {
        puts("*** Error joining on the first thread ***");
        return 2; // Returning because the program could not join on the first thread
    }
    // Create the second thread
    if ((check = pthread_create(&th2, NULL, calcAvgMed, NULL)) != 0) {
        puts("*** Error creating the second thread ***"); 
        return 3; // Returning because the second thread couldn't be created
    }
    // Create the third thread
    if ((check = pthread_create(&th3, NULL, calcMinMax, NULL)) != 0) {
        puts("*** Error creating the third thread ***");
        return 4; // Returning because the third thread couldn't be created
    }
    // Join on the second and third thread
    if ((check = pthread_join(th2, &ret1)) != 0) {
        puts("*** Error joining on the second thread ***");
        return 5; // Returning because the program could not join on the second thread
    }
    if ((check = pthread_join(th3, &ret2)) != 0) {
        puts("*** Error joining on the third thread ***");
        return 6; // Returning because the program could not join on the third thread
    }
    // Now that all the threads are finished, let the fourth thread clean everything up
    if ((check = pthread_create(&th4, NULL, cleanUp, NULL)) != 0) {
        puts("*** Error creating the fourth thread ***");
        return 7; // Returning because the fourth thread couldn't be created
    }
    if ((check = pthread_join(th4, &ret1)) != 0) {
        puts("*** Error joining on the fourth thread ***");
        return 8; // Returning because the program could not join on the fourth thread
    }

    // All done! Exit...
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
    char buff[80]; // Error check
    int nbyte;
    // Temp integer value
    int temp;
    // Reduced size
    int reducedArrSize = -1;

    // Ask for the integers from the user
    int i;
    puts("Enter up to 20 scores:");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("Enter score %d (-1 to quit):\n", i + 1);
        if ((nbyte = read(0, buff, 80)) == -1 ) {
            puts("*** Error reading in integers ***");
            pthread_exit(NULL);
            return NULL;
        }
        // Scan the value from the string
        if ((nbyte = sscanf(buff, "%d", &temp)) != 1) {
            puts("*** Error on parsing input ***");
            puts("Try inputting a number again...");
            i--;
            continue;
        }
        // Check if the user wants to exit
        if (temp == -1) {
            reducedArrSize = i;
            values[i] = 100000;
            break; 
        }
        if (temp < 0) {
            puts("*** Input can't be negative (outside of -1) ***");
            i--;
            continue;
        }
        // Assign the value to the array
        values[i] = temp;
    }
    if (reducedArrSize == -1) {
        reducedArrSize = ARRAY_SIZE; 
    }

    puts("Array values:");
    for (i = 0; i < reducedArrSize; i++) {
        printf("%d ", values[i]);
    }
    puts("");

    pthread_exit((void*)0);
    return NULL;
}

/*
 * calcAvgMed Function:
 * This function will wait for getTestScores to complete and then calculate 
 * the average and median scores out of the values in the array
 */
void* calcAvgMed(void* arg) {

    // Find the average in the array
    int i, sum = 0, shortenedSize = -1;
    for (i = 0; i < ARRAY_SIZE; i++) {
        // Value to indicate the array is shortened
        if (values[i] == 100000) {
            shortenedSize = i; 
            break;
        }
        sum += values[i];
    }
    // Make sure shortened size has something
    if (shortenedSize == -1) {
        shortenedSize = ARRAY_SIZE;
    }

    // Print the average and median
    if (shortenedSize == ARRAY_SIZE) {
        printf("Average: %f\n", (float)(sum / ARRAY_SIZE));
        // Find the median
        printf("Median = %f\n", ((float)(values[9] + values[10]) / 2));
    } else {
        // Find the median
        printf("Average: %f\n", ((float)sum / shortenedSize));
        if (shortenedSize % 2 == 0) {
            int temp = (shortenedSize - 1) / 2;
            printf("Median = %f\n", ((float)(values[temp] + values[temp + 1]) / 2));
        } else {
            printf("Median = %d\n", values[shortenedSize / 2]);
        }
    }

    pthread_exit((void*)0);
    return NULL;
}

/*
 * calcMinMax Function:
 * THis function will wait for getTestScores to complete and then calculate 
 * the minimum and maximum scores out of the values in the array
 */
void* calcMinMax(void* arg) {

    // Create the variables to hold the min and max
    int max = 0, min = 100000;
    // Find it
    int i;
    for (i = 0; i < ARRAY_SIZE && values[i] != 100000; i++) {
        if (values[i] > max) {
            max = values[i];
        }
        if (values[i] < min) {
            min = values[i];
        }
    }

    // Print out the values
    printf("Max = %d\n", max);
    printf("Min = %d\n", min);

    pthread_exit((void*)0);
    return NULL;
}

/*
 * cleanUp Function:
 * This function will wait until all threads are complete to clean up the buffer
 * and print out the result
 */
void* cleanUp(void* arg) {

    // Clean up the array and print it
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        values[i] = 0;
    }
    

    // Print it out
    puts("Cleaned array:");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", values[i]);
    }
    puts("");
    
    pthread_exit((void*)0);
    return NULL;
}
