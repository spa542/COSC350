#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/wait.h>

void handler(int sig) {
    if (sig == SIGUSR1) {
        puts("I am terminated by my parent"); 
        _exit(0);
    }
}

void handler2(int sig) {
    if (sig == SIGCHLD) {
        puts("My child is gone so I don't need to stay");
        exit(0);
    }
}

int main(void) {

    pid_t myID;

    myID = fork();
    if (myID == 0) {

        signal(SIGUSR1, handler);
        for ( ; true; ) {
            puts("child is running");
            sleep(1);
        }


    } else {
        int stat_val;
        waitpid(myID, &stat_val, WNOHANG | WUNTRACED);
        int i;
        signal(SIGCHLD, handler2);
        for (i = 0; true; i++) {
            if (i == 10) {
                kill(myID, SIGUSR1); 
            }
            puts("parent is running");
            sleep(1);
        }
    }

    return 0;
}
