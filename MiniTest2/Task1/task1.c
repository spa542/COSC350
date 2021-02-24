#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFFER_SIZE 1

int main(void) {
    
    // Create the buffer
    char buff[BUFFER_SIZE];

    int infd, outfd;

    infd = open("foo", O_RDONLY);
    if (infd == -1) {
        puts("*** Open Error ***");
        close(infd);
        close(outfd);
        return 1;
    }
    umask(0);
    outfd = open("symmetry", O_CREAT | O_WRONLY, 0600);
    if (outfd == -1) {
        puts("*** Open Error ***");
        close(infd);
        close(outfd);
        return 2;
    }

    int filesize = lseek(infd, 0, SEEK_END);
    int revcounter = -1;
    int nbyte;
    // Read and write the backwards portion
    lseek(infd, revcounter, SEEK_END);
    while((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
        if ((revcounter*-1) == filesize + 1) {
            break;
        }
        if (write(outfd, buff, BUFFER_SIZE) != nbyte) {
            puts("*** Write Error ***");
            close(infd);
            close(outfd);
            return 3;
        }
        revcounter--;
        lseek(infd, revcounter, SEEK_END);
    }
    // Add the special chars
    char specialBuff[] = {'|', '|'};
    if (write(outfd, specialBuff, 2) != 2) {
            puts("*** Write Error ***");
            close(infd);
            close(outfd);
            return 4;
    }
    // Now read the infd forwards
    lseek(infd, 0, SEEK_SET);
    while((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
        if (write(outfd, buff, BUFFER_SIZE) != nbyte) {
            puts("*** Write Error ***");
            close(infd);
            close(outfd);
            return 3;
        }
    }
    if (nbyte == -1) {
        puts("*** Read Error ***");
        close(infd);
        close(outfd);
        return 4;
    }

    // Close the files
    close(infd);
    close(outfd);
    
    return 0;
}
