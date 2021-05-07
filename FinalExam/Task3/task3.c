#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

void handler(int sig) {
    if(sig == SIGUSR1) {
        return;
    }
}

void parenthandler(int sig) {
    if (sig == SIGUSR1) {
        return;
    }
}

int main(void) {

    int myID;
    int fd;
    int mypipe[2];

    signal(SIGUSR1, parenthandler);

    pipe(mypipe); // create the pipe
    myID = fork();
    if (myID == 0) {
        signal(SIGUSR1, handler);
        char buffer[] = "Hi, Mom";
        fd = open("foo", O_CREAT | O_WRONLY, 0666);
        write(fd, buffer, 8);
        close(fd);
        kill(getppid(), SIGUSR1);
        pause();
        close(mypipe[1]);
        // Get from the pipe
        char buffer2[17];
        char myprintbuffer[] = "My mom said ";
        read(mypipe[0], buffer2, 17);
        char finalprint[17+12+1];
        strcpy(finalprint, myprintbuffer);
        strcat(finalprint, buffer2);
        printf("%s\n", finalprint);
    } else {
        pause(); // wait for child signal
        // Read from the file
        fd = open("foo", O_RDONLY);
        char buffer[8];
        char myprintbuffer[] = "My son said ";
        read(fd, buffer, 8);
        char finalbuff[8+12+1];
        strcpy(finalbuff, myprintbuffer);
        strcat(finalbuff, buffer);
        printf("%s\n", finalbuff);

        // Now write to the pipe
        char messagesend[] = "what do you want";
        close(mypipe[0]);
        write(mypipe[1], messagesend, 17);
        kill(myID, SIGUSR1);
    }


    return 0;
}
