#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<signal.h>

void* thrd1(void* arg) {
    int count = 1;
    while (true) {
        if (count == 10) {
            raise(SIGINT);
        }
        sleep(1);
        count++;
    }

    pthread_exit(0);
    return 0;
}

void* thrd2(void* arg) {
    while (true) {
        sleep(1);
    }

    pthread_exit(0);
    return 0;
}

int main(void) {

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thrd1, NULL);
    pthread_create(&thread2, NULL, thrd2, NULL);

    while (true) {
        sleep(1);
    }
    
    pthread_exit(0);
    return 0;
}
