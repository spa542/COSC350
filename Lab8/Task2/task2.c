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

/*
 * Three threads are sharing an integer array (global) and each do differenct 
 * jobs. Thread 1 will get up to 20 test scores from the keyboard and save
 * them into the array. Then, thread 2 will calculate an average score and
 * median value and display it while thread 3 will get the minimum and maximum
 * score and display it. Lastly, thread 4 will clear the buffer and set it to
 * 0 and display after thread 2 and 3 finished their job.
 */
int main(void) {

    return 0;
}
