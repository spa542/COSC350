/* 
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/18/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // read(), write()
#include<fcntl.h> // open()
#include<sys/stat.h> // S_I macros

#define BUFFER_SIZE 32

/*
 * Copy the contents of any readable file to a file with open()
 * function using a buffer with a size of 32 bytes
 */
int main(void) {

    // Create the buffer
    char buff[BUFFER_SIZE];
    // Name of input file
    char inFileName[] = "./foo";
    // Name of output file
    char outFileName[] = "./clone2";

    // Create the variable for the input file descriptor
    int infd;
    // Create the variable for the output file descriptor
    int outfd;
    // Open the file for reading
    infd = open(inFileName, O_RDONLY);
    // Check to make sure there is no error
    if (infd == -1) {
        puts("*** file already exists or could not be found ***");
        return 1; // Return because the open did not work
    }

    // Must set umask to 0 first so that nothing is "protected"
    // when creating a file with specific permission
    umask(0);
    // Open the file for writing
    outfd = open(outFileName, O_WRONLY | O_CREAT, 0770);
    // Check to make sure there is no error
    if (outfd == -1) {
        puts("*** error creating the file ***");
        close(infd);
        return 2; // Return because the open/creation did not work
    }

    // Create temporary return byte variable
    int nbyte;
    // Now read in all of the characters from the first file and write
    // them to the second file
    while ((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
        if (write(outfd, buff, nbyte) != nbyte) {
            puts("*** write error ***");
            // Close the files
            close(infd);
            close(outfd);
            return 3; // Return because the write did not work
        }
    }
    if (nbyte < 0) {
        puts("*** read error ***");
        close(infd);
        close(outfd);
        return 4; // Return because the read did not work properly
    }
    // Close the files
    close(infd);
    close(outfd);

    return 0;
}
