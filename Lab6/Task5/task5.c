/*
 * task5.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/11/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // fork(), exec()
#include<sys/types.h> // pid_t, getpid()
#include<fcntl.h> // open()
#include<stdbool.h> // bool alias
#include<sys/stat.h> // umask()

#define BUFFER_SIZE 1

/*
 * isNum Function:
 * Checks if the character passed is numeric or not
 */
bool isNum(char num) {
    // Check if the character is within the correct number range
    if (num >= '0' && num <= '9') {
        return true;
    }
    return false;
}

/*
 * Write a c program that receives an input file name as an 
 * argument and opens the file for input. Then, create a child 
 * process. The input file must open only once and the file descriptor
 * will be shared by the parent and child process. Both the parent and the
 * child will read one byte at a time from the input file and write
 * output to independent files (parent.txt and child.txt). The parent
 * process collects numeric characters and the child collects non-numeric
 * characters. Without any form of synchronization, the parent and child will
 * create wrong output files.
 * Modify the program to synchronize and get correct output for each process.
 * **Do not open the input file twice for synchronization
 * **Define your own function to check if the character is numeric
 * **Do not use vfork(), sleep(), wait(), or waitpid() for synchronization
 * **Check all possible errors for system calls
 */
int main(int argc, char** argv) {

    // Check for correct # of arguments
    if (argc != 2) {
        puts("*** Incorrect # of args ***");
        return 1; // Returning because the incorrect # of arguments was passed
    }
    // File descriptor for input
    int infd = open(argv[1], O_RDONLY);
    // error check
    if (infd == -1) {
        puts("*** error opening file for reading ***");
        return 2; // Returning because the file could not be opened for reading
    }
    // Create the child process
    pid_t pid = fork();
    // Create variable for output file for child
    int childOutfd;
    // Create variable for outpuf file for parent
    int parentOutfd;
    // Create buffer for child
    char childBuffer[BUFFER_SIZE];
    // Create buffer for parent
    char parentBuffer[BUFFER_SIZE];
    // Space buffer for both parent and child
    char spaceBuffer[] = {' '};
    // For new line
    char newLineBuffer[] = {'\n'};
    // Set the umask
    umask(0);
    // Start reading from the file 
    if (pid == 0) { // For the child
        // Need to use pread in order to keep buffers synchronized!!!!!!!
        int counter = 0; 
        // For error checking
        int nbyte;
        if ((childOutfd = open("child.txt", O_CREAT | O_WRONLY, 0666)) == -1) {
            puts("*** Error creating child.txt for write ***");
            _exit(3); // Returning because there was an error opening the file for writing
        }
        while ((nbyte = pread(infd, childBuffer, BUFFER_SIZE, counter++)) > 0) {
            if (isNum(childBuffer[0])) {
                // Write the number to the output file
                if (write(childOutfd, childBuffer, BUFFER_SIZE) == -1) {
                    puts("*** Error writing to child.txt ***");
                    _exit(4); // Returning because there was an error writing to the output file
                }
            } else if (childBuffer[0] == '\n') {
                // Write a new line to the output file
                if (write(childOutfd, newLineBuffer, BUFFER_SIZE) == -1) {
                    puts("*** Error writing to child.txt ***");
                    _exit(5); // Returning because there was an error writing to the output file
                }
            } else {
                // Write a space to the output file
                if (write(childOutfd, spaceBuffer, BUFFER_SIZE) == -1) {
                    puts("*** Error writing to child.txt ***");
                    _exit(6); // Returning because there was an error writing to the output file
                }
            }
        }
        if (nbyte == -1) {
            puts("*** Error reading from the input file for child ***");
            _exit(7); // Returning because there was an error reading the file for the child
        }
    } else { // For the parent
        // Need to use pread in order to keep buffers synchronized!!!!!!!
        int counter = 0; 
        // For error checking
        int nbyte;
        if ((parentOutfd = open("parent.txt", O_CREAT | O_WRONLY, 0666)) == -1) {
            puts("*** Error creating parent.txt for write ***");
            return 3; // Returning because there was an error opening the file for writing
        }
        while ((nbyte = pread(infd, parentBuffer, BUFFER_SIZE, counter++)) > 0) {
            if (isNum(parentBuffer[0])) {
                // Write a space to the output file
                if (write(parentOutfd, spaceBuffer, BUFFER_SIZE) == -1) {
                    puts("*** Error writing to parent.txt ***");
                    return 4; // Returning because there was an error writing to the output file
                }
            } else {
                // Write the non-numeric symbol to the output file
                if (write(parentOutfd, parentBuffer, BUFFER_SIZE) == -1) {
                    puts("*** Error writing to parent.txt ***");
                    return 5; // Returning because there was an error writing to the output file
                }
            }
        }
        if (nbyte == -1) {
            puts("*** Error reading from input file for child ***");
            return 6; // Returning because there was an error reading the file for the parent
        }
    }

    // Child exits with success if it makes it to here
    if (pid == 0) {
        _exit(0); 
    }

    // Make the parent close the file
    if (pid != 0) {
        close(infd);
    }

    return 0;
}
