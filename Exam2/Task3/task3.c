#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

void* fun1(void* arg) {
    return (void*)((long)arg + 10);
}

void* fun2(void* arg) {
    return (void*)((long)arg + 20);
}

void* fun3(void* arg) {
    return (void*)((long)arg + 30);
}

int main(int argc, char** argv) {

    if (argc != 2) {
        puts("*** Invalid # of arguments ***");
        return 1;
    }

    pthread_t thread1, thread2, thread3;
    void* status;

    long num = atoi(argv[1]);

    pthread_create(&thread1, NULL, fun1, (void*)num);
    pthread_join(thread1, &status);
    pthread_create(&thread2, NULL, fun2, (void*)status);
    pthread_join(thread2, &status);
    pthread_create(&thread3, NULL, fun3, (void*)status);
    pthread_join(thread3, &status);

    printf("The thread's calculation result is %ld\n", (long)status);

    pthread_exit(0);
    return 0;
}
