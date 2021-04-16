#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<stdbool.h>

// Global counter shared by threads
int counter = 0;

// Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thrd1(void* arg) {

    while (true) {
        if (counter < 10) {
            pthread_mutex_lock(&mutex);
            counter++;
            printf("%d\n", counter);
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(0);
    return 0;
}

void* thrd2(void* arg) {

    while (true) {
        if (counter > 0) {
            pthread_mutex_lock(&mutex);
            counter--;
            printf("%d\n", counter);
            pthread_mutex_unlock(&mutex);
        }
    }
    
    pthread_exit(0);
    return 0;
}

int main(void) {

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thrd1, NULL);
    pthread_create(&thread2, NULL, thrd2, NULL);

    pthread_exit(0);
    return 0;
}
