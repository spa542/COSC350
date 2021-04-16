#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<stdbool.h>

void handler(int sig) {
    if (sig == SIGUSR1) {
        puts("From now on, I am a zombie");
        exit(0);
    }
}

int main(void) {

    pid_t myID;

    myID = fork();

    if (myID == 0) { // Child
        signal(SIGUSR1, handler);
        while (true) {
            puts("I am your child");
            sleep(1);
        }
    } else { // Parent
        int i;
        while (true) {
            if (i == 10) {
                kill(myID, SIGUSR1);
            }
            puts("I am your parent");
            sleep(1);
            i++;
        }

    }

    return 0;
}
