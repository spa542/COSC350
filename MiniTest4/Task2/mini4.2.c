#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>

void threadhandler1(void* arg) {
    pthread_t cancelMe = *((pthread_t*)arg);
    puts("The first thread job is done");
    pthread_cancel(cancelMe);
}

void mainhandler(void* arg) {
    puts("The original thread job is done");
    exit(0);
}

void* t1(void* arg) {

    pthread_cleanup_push(threadhandler1, arg);
    while (true) {
        puts("This is the first thread");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);

    pthread_exit(0);
    return NULL;
}

void* t2(void* arg) {

    pthread_t cancelMe = *((pthread_t*)arg);
    int i;
    for (i = 0; true; i++) {
        if (i == 10) {
            pthread_cancel(cancelMe);
            puts("The second thread job is done");
            pthread_exit(0);
        }
        puts("This is the second thread");
        sleep(1);
    }

    pthread_exit(0);
    return NULL;
}

int main(void) {

    pthread_t thread1, thread2;
    pthread_t mainthread = pthread_self();

    int check;

    if ((check = pthread_create(&thread1, NULL, t1, (void*)&mainthread)) != 0) {
        puts("Error creating the first thread");
        return 1;
    }
    if ((check = pthread_create(&thread2, NULL, t2, (void*)&thread1)) != 0) {
        puts("Error creating the second thread");
        return 2;
    }

    pthread_cleanup_push(mainhandler, NULL);
    // Original thread print
    while (true) {
        puts("This is the original thread");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);


    return 0;
}
