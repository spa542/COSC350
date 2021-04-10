/*
 * pipeFifo.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/10/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<string.h> // String Functions
#include<unistd.h> // write(), read(), pipe()
#include<fcntl.h> // open()
#include<stdbool.h> // bool alias
#include<sys/stat.h> // mkfifo()
#include<sys/types.h> // Types

/*
 * Fifo is already created before hand in this program.
 * /tmp/task4_fifo
 */
int main(void) {
    int data_processed;
    char fifoName[] = "/tmp/task4_fifo";
    // Open the file descriptor to the fifo in non-blocking mode to start
    int readFd = open(fifoName, O_RDONLY | O_NONBLOCK);
    if (readFd == -1) {
        puts("*** Error opening the Fifo for reading ***");
        exit(EXIT_FAILURE);
    }
    int writeFd = open(fifoName, O_WRONLY);
    if (writeFd == -1) {
        puts("*** Error opening Fifo for writing ***");
        exit(EXIT_FAILURE);
    }
    // Change mode back to blocking
    fcntl(readFd, F_SETFL, 0);
    const char some_data[] = "123";
    char* buffer = (char*)malloc(strlen(some_data)*sizeof(char)+1);
    strcpy(buffer, some_data);
    data_processed = write(writeFd, some_data, strlen(some_data));
    printf("Wrote %d bytes\n", data_processed);
    data_processed = read(readFd, buffer, strlen(buffer));
    printf("Read %d bytes: %s\n", data_processed, buffer);
    // Close the fd's
    close(readFd);
    close(writeFd);
    exit(EXIT_SUCCESS);
}
