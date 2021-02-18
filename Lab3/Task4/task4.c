/* 
 * task4.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/18/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // read(), write(), lseek()
#include<fcntl.h> // open()
#include<sys/stat.h> // S_I macros

#define BUFFER_SIZE 1

/*
 * Copy the contents of any two readable files and append to a file
 * by using the lseek system call
 */
int main(void) {

    // Create the buffer
    char buff[BUFFER_SIZE];
    // Name of input file 1
    char inFileName1[] = "./foo";
    // Name of input file 2
    char inFileName2[] = "./foo1";
    // Name of output file
    char outFileName[] = "./foo12";

    // Create the variable for the first input file descriptor
    int infd1;
    // Create the variable for the second input file descriptor
    int infd2;
    // Create the variable for the output file descriptor
    int outfd;
    // Open the first file for reading
    infd1 = open(inFileName1, O_RDONLY);
    // Check to make sure there is no error
    if (infd1 == -1) {
        puts("*** file already exists or could not be found ***");
        return 1; // Return because the open did not work
    }
    // Open the seconf file for reading
    infd2 = open(inFileName2, O_RDONLY);
    // Check to make sure there is no error
    if (infd2 == -1) {
        puts("*** file already exists or could not be found ***");
        return 2; // Return because the open did not work
    }

    // Must set umask to 0 first so that nothing is "protected"
    // when creating a file with specific permission
    umask(0);
    // Open the file for writing
    outfd = open(outFileName, O_WRONLY | O_CREAT, 0760);
    // Check to make sure there is no error
    if (outfd == -1) {
        puts("*** error creating the file ***");
        close(infd1);
        close(infd2);
        return 3; // Return because the open/creation did not work
    }

    // Create temporary return byte variable
    int nbyte;
    // Now read in all of the characters from the first input file and write
    // them to the output file
    while ((nbyte = read(infd1, buff, BUFFER_SIZE)) > 0) {
        if (write(outfd, buff, nbyte) != nbyte) {
            puts("*** write error ***");
            // Close the files
            close(infd1);
            close(infd2);
            close(outfd);
            return 4; // Return because the write did not work
        }
    }
    if (nbyte < 0) {
        puts("*** read error ***");
        close(infd1);
        close(infd2);
        close(outfd);
        return 5; // Return because the read did not work properly
    }

    // We wrote into outfd from the first file, now we need to append 
    // the second file's info to the outfd
    // Move the cursor!
    lseek(outfd, 0, SEEK_END);

    // Now read in all of the characters from the first input file and write
    // them to the output file
    while ((nbyte = read(infd2, buff, BUFFER_SIZE)) > 0) {
        if (write(outfd, buff, nbyte) != nbyte) {
            puts("*** write error ***");
            // Close the files
            close(infd1);
            close(infd2);
            close(outfd);
            return 6; // Return because the write did not work
        }
    }
    if (nbyte < 0) {
        puts("*** read error ***");
        close(infd1);
        close(infd2);
        close(outfd);
        return 7; // Return because the read did not work properly
    }

    // Close the files
    close(infd1);
    close(infd2);
    close(outfd);

    return 0;
}
