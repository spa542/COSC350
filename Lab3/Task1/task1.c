/* 
 * task1.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/18/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // read(), write()

#define BUFFER_SIZE 1

/*
 * Copy the contents of any readable file to a file without
 * open() using standard input and output descriptors with redirection
 */
int main(void) {

    // Create the buffer
    char buff[BUFFER_SIZE];
    // Name of input file
    char inFileName[] = "./foo";
    // Name of output file
    char outFileName[] = "./clone";

    // Create temporary return byte variable
    int nbyte;

    // Read the standard input and write it to standard output
    // stdin is standard input equivalent to file descriptor 0
    // stdout is standard output equivalent ot file descriptor 1
    while ((nbyte = read(0, buff, BUFFER_SIZE)) > 0) {
        if (write(1, buff, nbyte) != nbyte) {
            puts("*** write error ***");
            return 1; // Return because the write did not work
        }
    }
    if (nbyte < 0) {
        puts("*** read error ***");
        return 2;  // Return because the read did not work properly
    }

    return 0;
}
