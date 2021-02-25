/*
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // lseek(), dup(), read()
#include<fcntl.h> // open()

#define BUFFER_SIZE 1

/*
 * palind() Function:
 * Takes two file descriptors that are open to the same
 * file and scans to see if the file contains a palindrome
 */
int palind(int fd1, int fd2) {
    
    // Create the forward and backward counter
    int forward = 0, backward = -2;
    // Create the read byte
    int nbyte;
    // Create the buffers
    char buff1[BUFFER_SIZE], buff2[BUFFER_SIZE];
    // Get the file size
    int filesize = lseek(fd1, 0, SEEK_END);
    
    // Prime the loop
    lseek(fd1, forward, SEEK_SET);
    while ((nbyte = read(fd1, buff1, BUFFER_SIZE)) > 0) {
        // Instant break out so that the backwards way doesnt break
        if (forward == filesize - 1) {
            break;
        }
        // First char was read, now lseek to the back and read the
        // char in the back to see if it matches
        lseek(fd2, backward, SEEK_END);
        if ((nbyte = read(fd2, buff2, BUFFER_SIZE)) > 0) {
            /* For testing if needed
            printf("buff1 = %c\n", buff1[0]);
            printf("buff2 = %c\n", buff2[0]);
            */
            if (buff1[0] != buff2[0]) {
                return 0;
            }
            // Increment the counters
            forward++;
            backward--;
            // Set the next forward lseek()
            lseek(fd1, forward, SEEK_SET);
        } else {
            puts("*** Read error ***");
            return 0; // Leave the function, something went wrong
        }
    }
    if (nbyte == -1) {
        puts("*** Read error ***");
        return 0; // Leave the function, something went wrong
    }
    
    return 1;
}

/*
 * Write a C-Function int palind(int fd1, int fd2) that
 * takes two file descriptors that are already opened to the same
 * file. Use lseek to scan the file and returns 1 if the file
 * contains a palindrome and 0 if not. Assume file is well formed
 * and contains just lower-case alphabetic chars on a single line.
 * Main function will accept a file name as an argument, opens the file
 * once, creates a duplicate file descriptor, and calls the palind()
 */
int main(int argc, char** argv) {

    // Check the arguments 
    if (argc != 2) {
        puts("*** Invalid # of args ***");
        return 1; // Returning because invalid # of args is read in
    }

    // Create the file descriptor variables
    int fd1, fd2;
    // Return var
    int rtn;

    // Open the file
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        puts("*** Error opening the file ***");
        return 2; // Returning because there was an error opening the file
    }

    // Duplicate the file descriptor using dup()
    fd2 = dup(fd1);

    // Call the palindrome function to check the file if there is a palindrome
    rtn = palind(fd1, fd2); 
    
    if (rtn == 1) {
        puts("Palindrome Found!");
    } else {
        puts("No Palindrome Found :(");
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);

    return 0;
}
