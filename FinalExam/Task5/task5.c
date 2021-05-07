#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<stdbool.h>

void handler(int sig) {
    if (sig == SIGUSR1) {
        puts("I am terminated by my parents");
        _exit(0);
    } else if (sig == SIGCHLD) {
        puts("My child is gone so I am now");
        exit(0);
    }
}

int main(void) {

    int myID;

    myID = fork();
    if (myID == 0) {
        signal(SIGUSR1, handler);
        while (true) {
            puts("child is running");
            sleep(1);
        }
    } else {
        signal(SIGCHLD, handler);
        int i = 0;
        while (true) {
            i++;
            puts("parent is running");
            sleep(1);
            if (i == 10) {
                kill(myID, SIGUSR1);
            }
        }
    }

    return 0;
}
