/*
 * task1.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/1/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<pthread.h> // Threading Library

#define NUM_THREADS 2

/*
 * sum Function:
 * This function will be called by a thread and will sum up the
 * 1 to the integer passed arg
 */
void* sum(void* arg) {
    int num = *((int*)arg);

    int i, sum = 0;
    for (i = 1; i <= num; i++) {
        sum += i;
    }
    
    printf("Sum: %d\n", sum);
    pthread_exit(NULL);
    return NULL;
}

/*
 * factorial Function:
 * This function will be called by a thread and will compute the factorial 
 * of the integer passed arg
 */
void* factorial(void* arg) {
    int num = *((int*)arg);

    int i, fact = 1;
    for (i = 1; i <= num; i++) {
        fact *= i; 
    }

    printf("Factorial: %d\n", fact);
    pthread_exit(NULL);
    return NULL;
}

/*
 * Write a C program which accepts an integer argument and calculates the
 * sum and the factorial up to the number passed  by using two threads to each do
 * their own task concurrently
 */
int main(int argc, char** argv) {

    // Check to make sure argument num is correct
    if (argc != 2) {
        puts("*** Invalid # of arguments ***");
        return 1; // Returning because the # of arguments is incorrect
    }

    // Get the value from the command line
    int n = atoi(argv[1]);

    // Make sure it is valid
    if (n < 0) {
        puts("*** Invalid input, must be positive! ***");
        return 2; // Returning because the argument is not positive
    }

    // Create the thread variables;
    pthread_t thread1, thread2;
    // Error check
    int check;
    if ((check = pthread_create(&thread1, NULL, sum, (void*)&n)) != 0) {
        puts("*** Error creating the first thread ***");
        return 3; // Returning because the first thread couldn't be created
    }
    if ((check = pthread_create(&thread2, NULL, factorial, (void*)&n)) != 0) {
        puts("*** Error creating the second thread ***");
        return 4; // Returning because the second thread couldn't be created
    }
    // Kill the threads
    pthread_exit(NULL);
    
    // All done!
    return 0;
}
