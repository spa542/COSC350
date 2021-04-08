/*
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/1/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // pipe()
#include<sys/types.h> // pid_t
#include<string.h> // String functions

#define BUFFER_SIZE 80

/*
 * A parent process asks for two integers from the command line and 
 * sends them to the child by using a pipe. The child process makes sure
 * that the two inputs are valid integers. The child process then calculates
 * the sum of the two integers and outputs them to standard output. The child
 * process process continues until input from the parent is EOF.
 */
int main(void) {

    // Create the descriptor array
    int mypipe[2];
    // Create the variable for pid
    pid_t myID;

    // Create the pipe
    if (pipe(mypipe) < 0) {
        puts("*** Error creating the pipe ***");
        return 1; // Returning because there was an error creating the pipe
    }

    // Fork the child process
    if ((myID = fork()) < 0) {
        puts("*** Error forking ***"); 
        return 2; // Returning because there was an error forking a child process
    }
   
    // Do stuff
    if (myID == 0) { // Child
        // Close the writing to pipe end
        close(mypipe[1]);

        // Check byte
        int nbyte;
        // Create buffer
        char buffer[BUFFER_SIZE];
        // Create the integer variables to add
        int one, two;

        while ((nbyte = read(mypipe[0], buffer, BUFFER_SIZE)) > 0) {
            if (sscanf(buffer, "%d%d", &one, &two) == 2) { // Success
                printf("Sum: %d + %d = %d\n", one, two, one + two);
            } else { // Fail
                puts("*** Error wrong inputs ***");
                //_exit(5); // Returning because the sscanf did not read two integers properly
            }
        }

        // All done
        _exit(0);
    } else { // Parent
        // Close the reading to pipe end
        close(mypipe[0]);

        // Create the buffer
        char buffer[BUFFER_SIZE];
        // Check byte
        char nbyte;

        // Write to the pipe
        puts("Enter two integers:");
        while((nbyte = read(0, buffer, BUFFER_SIZE)) > 0) {
            if (write(mypipe[1], buffer, nbyte) != nbyte) {
                puts("*** Error writing to pipe ***");
                return 4; // Returning because there was an error writing to the pipe
            }
        }
        // Error check read
        if (nbyte == -1) {
            puts("*** Error reading ***");
            return 3; // Returning because there was an error with the read function
        }
    }

    return 0;
}
