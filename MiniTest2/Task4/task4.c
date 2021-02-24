#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFFER_SIZE 1

int main(int argc, char** argv) {

    // Create the buffer
    char buff[BUFFER_SIZE];

    // Make sure argument count is right
    if (argc != 2) {
        puts("*** Incorrect # of arguments ***");
        return 1;
    }
    int infd;

    infd = open(argv[1], O_RDONLY);
    if (infd == -1) {
        puts("*** Read Error ***");
        return 2;
    }

    int counter = 0;
    int nbyte;
    while((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
        counter++; 
    }
    if (nbyte == -1) {
        puts("*** Read Error ***");
        close(infd);
        return 3;
    }
    
    // Print
    printf("The size of the file in bytes is %d\n", counter);

    // Close the file
    close(infd);

    return 0;
}
