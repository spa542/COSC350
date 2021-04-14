#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main(void) {

    int check;
    int pipe1[2];
    int pipe2[2];
    pid_t myID;

    pipe(pipe1);
    pipe(pipe2);

    myID = fork();
    if (myID == 0) { // Child
        char message[] = "Hi, Mom"; 
        char buffer[80];
        char mypart[] = "My mom said ";
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], message, sizeof(message));
        read(pipe2[0], buffer, sizeof(buffer));

        char printBuffer[sizeof(mypart)+sizeof(buffer)+1];
        strcpy(printBuffer, mypart);
        strcat(printBuffer, buffer);
        printf("%s\n", printBuffer);

    } else { // Parent
        char message[] = "I love you";
        char buffer[80];
        char mypart[] = "My child said ";
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], buffer, sizeof(buffer));
        write(pipe2[1], message, sizeof(message));

        char printBuffer[sizeof(mypart)+sizeof(buffer)+1];
        strcpy(printBuffer, mypart);
        strcat(printBuffer, buffer);
        printf("%s\n", printBuffer);

    }

    return 0;
}
