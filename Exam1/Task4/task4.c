#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdbool.h>

#define BUFFER_SIZE 1

int main(int argc, char** argv) {

    if (argc != 6) {
        puts("*** Incorrect # of args ***");
        return 1;
    }

    int infd, outfd1, outfd2, outfd3, outfd4;

    infd = open(argv[1], O_RDONLY);
    if (infd == -1) {
        puts("*** Error opening read file ***");
        return 2;
    }
    umask(0);
    outfd1 = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if (outfd1 == -1) {
        puts("*** Error opening write file ***");
        return 3;
    }
    outfd2 = open(argv[3], O_WRONLY | O_CREAT, 0666);
    if (outfd2 == -1) {
        puts("*** Error opening write file ***");
        return 4;
    }
    outfd3 = open(argv[4], O_WRONLY | O_CREAT, 0666);
    if (outfd3 == -1) {
        puts("*** Error opening write file ***");
        return 5;
    }
    outfd4 = open(argv[5], O_WRONLY | O_CREAT, 0666);
    if (outfd4 == -1) {
        puts("*** Error opening write file ***");
        return 6;
    }

    int nbyte;
    char buff[BUFFER_SIZE];
    char spaceBuff[] = {' '};

    while ((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
        if (buff[0] >= '0' && buff[0] <= '9') {
            write(outfd1, spaceBuff, BUFFER_SIZE);
            write(outfd2, buff, BUFFER_SIZE);
            write(outfd3, spaceBuff, BUFFER_SIZE);
        } else if ((buff[0] >= 'A' && buff[0] <= 'Z') || (buff[0] >= 'a' && buff[0] <= 'z')) {
            write(outfd1, buff, BUFFER_SIZE);
            write(outfd2, spaceBuff, BUFFER_SIZE);
            write(outfd3, spaceBuff, BUFFER_SIZE);
        } else {
            if (buff[0] == '\n') {
                write(outfd1, buff, BUFFER_SIZE);
                write(outfd2, buff, BUFFER_SIZE);
                write(outfd3, buff, BUFFER_SIZE);
                continue;
            }
            write(outfd1, spaceBuff, BUFFER_SIZE);
            write(outfd2, spaceBuff, BUFFER_SIZE);
            write(outfd3, buff, BUFFER_SIZE);
        }
    }

    close(infd);
    close(outfd1);
    close(outfd2);
    close(outfd3);
            

    umask(0);
    outfd1 = open(argv[2], O_RDONLY);
    if (outfd1 == -1) {
        puts("*** Error opening read file ***");
        return 6;
    }
    outfd2 = open(argv[3], O_RDONLY);
    if (outfd2 == -1) {
        puts("*** Error opening read file ***");
        return 7;
    }
    outfd3 = open(argv[4], O_RDONLY);
    if (outfd3 == -1) {
        puts("*** Error opening read file ***");
        return 8;
    }
    
    // Prime the loop
    nbyte = 5;
    bool moveOn = false;
    while (nbyte > 0) {
        // Read from first file 
        nbyte = read(outfd1, buff, BUFFER_SIZE);
        if (buff[0] == '\n') {
            write(outfd4, buff, BUFFER_SIZE);
            moveOn = true;
        } 
        if (buff[0] != ' ' && !moveOn) {
            write(outfd4, buff, BUFFER_SIZE);
            moveOn = true;
        }
        // Read from second file
        nbyte = read(outfd2, buff, BUFFER_SIZE);
        if (buff[0] != ' ' && !moveOn) {
            write(outfd4, buff, BUFFER_SIZE); 
            moveOn = true;
        }
        // Read for third file
        nbyte = read(outfd3, buff, BUFFER_SIZE);
        if (!moveOn) {
            write(outfd4, buff, BUFFER_SIZE);
            moveOn = true;
        }
        moveOn = false;
    }

    close(outfd1);
    close(outfd2);
    close(outfd3);
    close(outfd4);

    return 0;
}
