/*
 * task5.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/18/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // read(), write(), lseek()
#include<fcntl.h> // open()
#include<sys/stat.h> // umask()

#define BUFFER_SIZE 1

/*
 * Open a file as input and write into a file in reverse order 
 * using lseek() system call
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
    int revcounter = -1;
    // Byte check
    int nbyte;
    // Now write the contents of input file in reverse to output file
    // Use lseek() to move the cursor to the end of the file and read byte by
    // byte until the beginning and then write to the output file
    // Get the file size
    int filesize = lseek(infd, 0, SEEK_END);
    // Start the cursor at the end of the file
    lseek(infd, revcounter, SEEK_END);
    while((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
        if (write(outfd, buff, BUFFER_SIZE) != nbyte) {
            puts("*** error writing to file ***");
            close(infd);
            close(outfd);
            return 3; // Return because the write did not work 
        }
        if ((revcounter*-1) == filesize) {
            break;
        }
        revcounter--;
        lseek(infd, revcounter, SEEK_END);
    }
    if (nbyte < 0) {
        puts("*** error reading from file ***");
        close(infd);
        close(outfd); 
        return 4; // Return because the read did not work
    }

    // Close the files
    close(infd);
    close(outfd);

    return 0;
}
