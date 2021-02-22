/*
 * task6.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/18/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // read(), write(), pread()
#include<fcntl.h> // open()
#include<sys/stat.h> // umask()

#define BUFFER_SIZE 1

/*
 * writeFileReverse() Function:
 * This function will read from a file using pread() 
 * and then write the contents of the file byte by byte
 * in reverse order
 */
int writeFileReverse(int infd, int outfd, int offsetStart) {
    // Create the local buffer
    char localBuff[BUFFER_SIZE];
    // Walk up the recursive call stack until we cant read anymore 
    // chars and then write the char as we walk back down the stack
    if (pread(infd, localBuff, BUFFER_SIZE, offsetStart) > 0) {
        writeFileReverse(infd, outfd, offsetStart + 1);
        write(outfd, localBuff, BUFFER_SIZE);
    }
    return 0; // Return 0 because the function worked properly
}

/*
 * Open a file as input and write into a file in reverse order 
 * using pread() system call
 */
int main(void) {

    // Create the input file descriptor variable
    int infd;
    // Create the output file descriptor variable
    int outfd;
    // Create the buffer
    char buff[BUFFER_SIZE];

    // Create the string that stores the name of the input file
    char inFileName[] = "./foo";
    // Create the string that stores the name of the output file
    char outFileName[] = "./foorev";

    // Open the specified input file
    infd = open(inFileName, O_RDONLY);
    // Check for error
    if (infd == -1) {
        puts("*** error opening input file ***");
        return 1; // Return because input file did not open correctly
    }

    // Set the umask to 0 so there is no protections
    umask(0);

    // Open the specified output file
    outfd = open(outFileName, O_CREAT | O_WRONLY, 0760);
    // Check for error
    if (outfd == -1) {
        puts("*** error opening or creating the output file ***");
        close(infd);
        return 2; // Return because output file did not create/open correctly
    }

    // Reverse counter
    int revcounter;
    // Byte check
    int nbyte;

    // Call the function
    writeFileReverse(infd, outfd, 0);

    // Close the files
    close(infd);
    close(outfd);

    return 0;
}
