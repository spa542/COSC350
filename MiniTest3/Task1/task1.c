#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(void) {

    pid_t myId1 = fork();

    if (myId1 == 0) { // Child
        pid_t myId2 = fork();
        if (myId2 == 0) { // Grandchild
            // Runs forever
            // Will exit when parent dies
            int stat_val2 = -1;
            int my_local_return;
            pid_t originalParentPid = getppid();
            pid_t myParentPid = getppid();
            while(true) {
                myParentPid = getppid();
                if (myParentPid != originalParentPid) {
                    puts("I'm the grandchild, my parent died so I go too!");
                    _exit(0);
                }
                puts("I am your grandchild");
                sleep(1);
            }
        } else { // Child
            int i;
            // Terminates after 100 rounds
            for (i = 0; i < 100; i++) {
                puts("I am your child");
                sleep(1);
            }
            //kill(myId2, SIGKILL);
            _exit(0);
        }
    } else { // Parent
        int i; 
        int stat_val = -1;
        int child_pid;
        while(true) {
            child_pid = waitpid(myId1, &stat_val, WNOHANG);
            if (WIFEXITED(stat_val)) {
                puts("I finish my job");
                exit(0);
            }
            puts("I am your parent");
            sleep(1);
        }
    }

    exit(0);
}
